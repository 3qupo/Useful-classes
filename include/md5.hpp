#include <iostream>
#include <cstdint>

class MD5
{
private:
    std::uint32_t _state[4];            // Основные регистры A, B, C, D
    uint64_t _count;                    // Счетчик обработанных бит
    uint8_t _buffer[64];                // Буфер для текущего блока 
    bool _finalized;                    // Флаг, что хеш вычислен
    uint8_t _digest[16];                // Финальный хеш
    uint32_t leftRotate(uint32_t x, uint8_t n);

    static const uint32_t K[64];        // Синус-константы
    static const uint8_t S[64];         // Величины сдвигов

public:
    MD5();                                           // Инициализация
    MD5(const std::string& str);                     // Инициализация с данными                       
        
    void init();                                     // Сброс состояния
    void update(const uint8_t* data, size_t length); // Добавление данных
    void update(const std::string& str);             // Добавление строки

    void finalize();                                 // Завершение хеширования
    std::string hexdigest() const;                   // 32 hex символа
    std::string digest() const;                      // бинарный хеш (16 байт)

    static std::string hash(const std::string& str);                        
    static std::string hash(const uint8_t* data, size_t length);

    friend std::ostream& operator << (std::ostream& os, const MD5& md5);
};