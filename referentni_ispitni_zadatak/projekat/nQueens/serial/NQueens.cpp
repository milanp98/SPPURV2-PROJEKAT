#include "NQueens.h"

CNQueens::CNQueens(CTask* updateUniqueSolutionsNo, CTask* passResult)
{
    this->updateUniqueSolutionsNo = updateUniqueSolutionsNo;
    this->passResult = passResult;
	uniqueSolutionsNo=0;
	totalSolutionsNo=0;
}

CNQueens::~CNQueens(void)
{
}

void CNQueens::Solve()
{
	uniqueSolutionsNo=0;
	totalSolutionsNo=0;

    for(int i=0; i<n; i++) {
	    // try all positions in first row
        column[0] = i;
		TryPlace(1);
    }
}

void CNQueens::Print()
{
    cout<<"N="<<n<<endl;
	cout<<"Number of solutions: "<<totalSolutionsNo<<endl;
	cout<<"Number of unique solutions: "<<uniqueSolutionsNo<<endl;
	cout<<endl;
	cout<<endl;
}

void CNQueens::TryPlace(int i)
{
	if (!IsAttacked(i-1))
    {
		if (i==n)
        {
			totalSolutionsNo++;
            UniqueSolutionParam param;
            param.column = column;
            param.n = n;
            param.uniqueSolutionsNo = &uniqueSolutionsNo;
            updateUniqueSolutionsNo->Run(&param);
		}
		else
        {
			for (int j=0; j<n; j++)
            {
				column[i]=j;
				TryPlace(i+1);
			}
		}
	}
}

bool CNQueens::IsAttacked(int i)
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

int CNQueens::Run(void* param)
{
    int n = -1;
    if(param!=NULL)
    {
        n = *(int*)param;
    }

    if(n<=0)
    {
        return -1;
    }

    this->n = n;
    column = new int[n];

    this->Solve();

    ResultsCollectorParam results;
    results.n = n;
    results.totalSolutionsNo = totalSolutionsNo;
    results.uniqueSolutionsNo = uniqueSolutionsNo;

    passResult->Run(&results);

    delete[] column;

    return 0;
}
