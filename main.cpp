#include "include/structs/LongNumber.hpp"
#include "include/structs/Matrix.hpp"
#include "include/structs/Generator.hpp"
#include "include/tests.hpp"
#include "include/structs/Graph.hpp"
#include "include/structs/BinarySearchTree.hpp"
#include "src/networks/database/Database.hpp"
#include "src/networks/database/ChatDatabase.hpp"
#include "src/networks/database/EchoDatabase.hpp"

using namespace std;
using namespace Generator;
using namespace testsLongNumber;
using namespace testMatrix;

LongNumber my_sqrt(LongNumber number);
void fermat_factorization(LongNumber& number);

int main() 
{
    Database db;
    db.connect("localhost", "5432", "my_own_db", "Andrei", "1234");
    db.disconnect();
    
    return 0;
}