#include "../include/LongNumber.h"
#include "../include/Matrix.h"
#include "../include/Generator.h"
#include "../include/tests.h"

using namespace std;
using namespace Generator;
using namespace testsLongNumber;
using namespace testMatrix;

int main() 
{
    
    cout << "Starting LongNumber tests..." << endl << endl;
    
    try {
        
        testAssignmentOperatorLongNumber();
        cout << endl;
        
        testIndexOperatorLongNumber();
        cout << endl;
        
        testArithmeticOperatorsWithLongNumber();
        cout << endl;
        
        testArithmeticOperatorsLongNumberWithInt();
        cout << endl;
        
        testComparisonOperatorsWithLongNumber();
        cout << endl;
        
        testComparisonOperatorsLongNumberWithInt();
        cout << endl;
        
        testEdgeCasesLongNumber();
        cout << endl;
        
        testMixedOperationsLongNumber();
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