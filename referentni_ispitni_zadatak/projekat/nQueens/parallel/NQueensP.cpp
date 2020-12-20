#include "NQueensP.h"

// define tbb mutexes
spin_mutex NrOfSolutionsMutex;

CNQueensP::CNQueensP(int n, concurrent_queue<ResultsCollectorParam*>* result_queue) : result_queue(result_queue)
{
    this->n = n;
}

CNQueensP::~CNQueensP(void)
{
}

void CNQueensP::Solve()
{
	uniqueSolutionsNo=0;
	totalSolutionsNo=0;

	// Do a parallel for over the n positions in the first row.
	// Let the scheduler decide how the n tasks are distrubuted 
	// on the different threads
	parallel_for(blocked_range<size_t>(0, n, 1), SetQueens(n, &totalSolutionsNo, &queue));
}

void CNQueensP::Print()
{
    cout<<"N="<<n<<endl;
	cout<<"Number of solutions: "<<totalSolutionsNo<<endl;
	cout<<"Number of unique solutions: "<<uniqueSolutionsNo<<endl;
	cout<<endl;
	cout<<endl;
}

void TryPlace(int* column, int i, int n, int* totalSolutionsNo, concurrent_queue<int*>* queue)
{
	if (!IsAttacked(column, i-1, n))
    {
		if (i==n)
        {
            spin_mutex::scoped_lock mylock(NrOfSolutionsMutex);
			(*totalSolutionsNo)++;
            int* columnCopy = new int[n];
            memcpy(columnCopy, column, n*sizeof(int));
            queue->push(columnCopy);
		}
		else
        {
			for (int j=0; j<n; j++)
            {
				column[i]=j;
				TryPlace(column, i+1, n, totalSolutionsNo, queue);
			}
		}
	}
}

bool IsAttacked(int* column, int i, int n)
{
	for (int k=0; k<i; k++)
    {
		if (column[i]==column[k] || abs(column[i]-column[k])==i-k)
        {
			return true;
        }
    }
	return false;
}

task* CNQueensP::execute()
{
    // run uniqueSolutionsTask
    CUniqueSolutionP *uniqueSolution = new( tbb::task::allocate_child() ) CUniqueSolutionP(n, &queue, &uniqueSolutionsNo);
    uniqueSolution->set_ref_count(0);
    this->increment_ref_count();
    task::spawn(*uniqueSolution);

    Solve();

    // send last one as notification that NQueens has found the last solution
    queue.push(NULL);

    this->wait_for_all();

    // pass results
    ResultsCollectorParam* results = new ResultsCollectorParam;
    results->n = n;
    results->totalSolutionsNo = totalSolutionsNo;
    results->uniqueSolutionsNo = uniqueSolutionsNo;
    result_queue->push(results);

    return NULL;
}

void SetQueens::operator()( const blocked_range<size_t>& r ) const {
	for( size_t i=r.begin(); i!=r.end(); ++i ) {
        // try all positions in first row
		// create separate array for each recursion
		// started here
        int* column = new int[n];
        column[0] = i;
        TryPlace(column, 1, n, totalSolutionsNo, queue);
    }
}
