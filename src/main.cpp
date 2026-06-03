#include "../include/LongNumber.h"
#include "../include/Matrix.h"
#include "../include/Generator.h"
#include "../include/tests.h"
#include "../include/Graph.h"
#include "../include/BinarySearchTree.h"

using namespace std;
using namespace Generator;
using namespace testsLongNumber;
using namespace testMatrix;

int main() 
{
    
    cout << "Starting LongNumber tests..." << endl << endl;

    try {
        
        testCreateMatrix();
        cout << endl;
        
        testAssignmentOperatorMatrix();
        cout << endl;
        
        testArithmeticOperatorsWithLongNumber();
        cout << endl;
        
        testArithmeticOperatorsWithMatrix();
        cout << endl;
        
        testArithmeticOperatorsMatrixWithInt();
        cout << endl;
        
        testEdgeCasesMatrix();
        cout << endl;
        
        cout << "====================================" << endl;
        cout << "ALL TESTS PASSED SUCCESSFULLY!" << endl;
        cout << "====================================" << endl;
        
    } catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "Test failed with unknown exception" << endl;
        return 1;
    }
    
    return 0;
}