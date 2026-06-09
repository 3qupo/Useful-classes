#include "include/structs/LongNumber.hpp"
#include "include/structs/Matrix.hpp"
#include "include/structs/Generator.hpp"
#include "include/tests.hpp"
#include "include/structs/Graph.hpp"
#include "include/structs/BinarySearchTree.hpp"
#include "src/networks/database/ChatDatabase.hpp"
#include "src/networks/database/EchoDatabase.hpp"
#include "src/networks/database/Database.hpp"

using namespace std;
using namespace Generator;
using namespace testsLongNumber;
using namespace testMatrix;

LongNumber my_sqrt(LongNumber number);
void fermat_factorization(LongNumber& number);

int main() 
{
    EchoDatabase db;
    
    if (!db.connect("localhost", "5433", "my_own_db", "postgres", "1234")) {
        std::cout << "Ошибка: " << db.getLastError() << std::endl;
        return 1;
    }
    
    std::cout << "Подключено!" << std::endl;
   
    if (db.logMessage("127.0.0.1", "Hello, PostgreSQL!")) {
        std::cout << "Сообщение сохранено" << std::endl;
    } else {
        std::cout << "Ошибка: " << db.getLastError() << std::endl;
    }
    
    auto messages = db.getRecentMessage(5);
    std::cout << "\nПоследние сообщения:" << std::endl;
    for (const auto& msg : messages) {
        std::cout << " - " << msg << std::endl;
    }
    
    db.disconnect();
    
    return 0;
}