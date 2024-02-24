#ifdef TEST

#include <stddef.h>
#include "unity.h"
#include "GPIO.h"


#define GPIO_CLR_MASK				0x00000003U
#define GPIO_MODE_MASK				0x00000003U		/*Input,output,AF or AN*/
#define GPIO_TYPE_MASK				0x00000001U		/*PushPull or OpenDrain*/
#define GPIO_PUPD_MASK				0x00000018U
#define GPIO_BSRR_RESET_OFFSET		16U

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_MODE_IN_FL)               ||\
                            ((MODE) == GPIO_MODE_IN_PU)               ||\
                            ((MODE) == GPIO_MODE_IN_PD)               ||\
                            ((MODE) == GPIO_MODE_OUT_PP)              ||\
                            ((MODE) == GPIO_MODE_OUT_PP_PU)           ||\
                            ((MODE) == GPIO_MODE_OUT_PP_PD)           ||\
                            ((MODE) == GPIO_MODE_OUT_OD)              ||\
                            ((MODE) == GPIO_MODE_OUT_OD_PU)           ||\
                            ((MODE) == GPIO_MODE_OUT_OD_PD)           ||\
                            ((MODE) == GPIO_MODE_AF_PP)               ||\
                            ((MODE) == GPIO_MODE_AF_PP_PU)            ||\
                            ((MODE) == GPIO_MODE_AF_PP_PD)            ||\
                            ((MODE) == GPIO_MODE_AF_OD)               ||\
                            ((MODE) == GPIO_MODE_AF_OD_PU)            ||\
                            ((MODE) == GPIO_MODE_AF_OD_PD)            ||\
                            ((MODE) == GPIO_MODE_AN))

typedef struct{
	volatile u32 MODER;
	volatile u32 OTYPER;
	volatile u32 OSPEEDR;
	volatile u32 PUPDR;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 LCKR;
	volatile u32 AFRL;
	volatile u32 AFRH;
}GPIO_Registers_t;

void test_GPIO_Init_ValidCfg(void) {
    GPIO_Registers_t mock_GPIO_Port;
    void* GPIO_Port = &mock_GPIO_Port;
    GPIO_Pin_t gpioPinConfig = {
        .GPIO_Pin = GPIO_PIN_0,
        .GPIO_Port = GPIO_Port,
        .GPIO_Speed = GPIO_SPEED_LOW,
        .GPIO_Mode = GPIO_MODE_OUT_PP
    };

    GPIO_ErrorStatus_t result = GPIO_Init(&gpioPinConfig);

    TEST_ASSERT_EQUAL(GPIO_OK, result);
}


void test_GPIO_Init_InvalidPin(void) {
    GPIO_Registers_t mock_GPIO_Port;
    void* GPIO_Port = &mock_GPIO_Port;
    GPIO_Pin_t gpioPinConfig = {20, GPIO_Port, GPIO_SPEED_LOW, GPIO_MODE_OUT_PP};
    TEST_ASSERT_EQUAL(GPIO_InvalidPin, GPIO_Init(&gpioPinConfig));
}

void test_GPIO_Init_InvalidMode(void) {
    GPIO_Registers_t mock_GPIO_Port;
    void* GPIO_Port = &mock_GPIO_Port;
    GPIO_Pin_t gpioPinConfig = {GPIO_PIN_0, GPIO_Port, GPIO_SPEED_LOW, 0xff};   /*0xff represent any other mode*/
    TEST_ASSERT_EQUAL(GPIO_InvalidMode, GPIO_Init(&gpioPinConfig));
}

void test_GPIO_Init_InvalidSpeed(void) {
    GPIO_Registers_t mock_GPIO_Port;
    void* GPIO_Port = &mock_GPIO_Port;
    GPIO_Pin_t gpioPinConfig = {GPIO_PIN_0, GPIO_Port, 0xff, GPIO_MODE_OUT_PP};   /*0xff represent any other speed*/
    TEST_ASSERT_EQUAL(GPIO_InvalidSpeed, GPIO_Init(&gpioPinConfig));
}


void test_GPIO_setPinValue_validSetState(void) {
    /* Mock GPIO port structure for testing */
    GPIO_Registers_t mock_GPIO_Port;

    /* Initialize GPIO port and pin */
    void* GPIO_Port = &mock_GPIO_Port;

    u8 GPIO_pin = GPIO_PIN_10;

    /* Call GPIO_setPinValue with GPIO_STATE_SET */
    GPIO_ErrorStatus_t result = GPIO_setPinValue(GPIO_Port, GPIO_pin, GPIO_STATE_SET);

    /* Check if the function returns GPIO_OK */
    TEST_ASSERT_EQUAL_INT(GPIO_OK, result);

    /* Check if the BSRR register was set correctly */
    TEST_ASSERT_EQUAL_HEX32((GPIO_STATE_SET << GPIO_pin), mock_GPIO_Port.BSRR);
}

void test_GPIO_setPinValue_validResetState(void) {
    /* Mock GPIO port structure for testing */
    GPIO_Registers_t mock_GPIO_Port;

    /* Initialize GPIO port and pin */
    void* GPIO_Port = &mock_GPIO_Port;
    u8 GPIO_pin = GPIO_PIN_3;

    /* Call GPIO_setPinValue with GPIO_STATE_RESET */
    GPIO_ErrorStatus_t result = GPIO_setPinValue(GPIO_Port, GPIO_pin, GPIO_STATE_RESET);

    /* Check if the function returns GPIO_OK */
    TEST_ASSERT_EQUAL_INT(GPIO_OK, result);

    /* Check if the BSRR register was set correctly */
    TEST_ASSERT_EQUAL_HEX32((1 << (GPIO_pin + GPIO_BSRR_RESET_OFFSET)), mock_GPIO_Port.BSRR);
}

void test_GPIO_setPinValue_nullPointer(void) {
    /* Call GPIO_setPinValue with a null pointer */
    GPIO_ErrorStatus_t result = GPIO_setPinValue(NULL_PTR, 2, GPIO_STATE_SET);

    /* Check if the function returns GPIO_NULLPTR */
    TEST_ASSERT_EQUAL_INT(GPIO_NULLPTR, result);
}

void test_GPIO_setPinValue_invalidPin(void) {
    /* Mock GPIO port structure for testing */
    GPIO_Registers_t mock_GPIO_Port;

    /* Initialize GPIO port and an invalid pin */
    void* GPIO_Port = &mock_GPIO_Port;
    u8 invalid_pin = 20;  /* Choose an invalid pin number */

    /* Call GPIO_setPinValue with an invalid pin */
    GPIO_ErrorStatus_t result = GPIO_setPinValue(GPIO_Port, invalid_pin, GPIO_STATE_SET);

    /* Check if the function returns GPIO_InvalidPin */
    TEST_ASSERT_EQUAL_INT(GPIO_InvalidPin, result);
}

void test_GPIO_setPinValue_invalidState(void) {
    /* Mock GPIO port structure for testing */
    GPIO_Registers_t mock_GPIO_Port;

    /* Initialize GPIO port and pin */
    void* GPIO_Port = &mock_GPIO_Port;
    u8 GPIO_pin = 8;

    /* Call GPIO_setPinValue with an invalid state */
    GPIO_ErrorStatus_t result = GPIO_setPinValue(GPIO_Port, GPIO_pin, 42);  /* 42 is an arbitrary invalid state */

    /* Check if the function returns GPIO_InvalidState */
    TEST_ASSERT_EQUAL_INT(GPIO_InvalidState, result);
}

void test_GPIO_getPinValue_validStateSet(void) {
    /* Mock GPIO port structure for testing */
    GPIO_Registers_t mock_GPIO_Reg;
    mock_GPIO_Reg.IDR = 0b00100000; // Assuming GPIO_pin 5 is set in the IDR

    /* Initialize GPIO port and pin */
    GPIO_Registers_t* GPIO_Base_Reg = &mock_GPIO_Reg;

    void* GPIO_Port = GPIO_Base_Reg; // Use the address of the mock structure

    u8 GPIO_pin = 5;
    u8 GPIO_State;

    /* Call GPIO_getPinValue */
    GPIO_ErrorStatus_t result = GPIO_getPinValue(GPIO_Port, GPIO_pin, &GPIO_State);

    /* Check if the function returns GPIO_OK */
    TEST_ASSERT_EQUAL_INT(GPIO_OK, result);

    /* Check if GPIO_State is set to GPIO_STATE_SET */
    TEST_ASSERT_EQUAL_INT(GPIO_STATE_SET, GPIO_State);
}

void test_GPIO_getPinValue_validStateReset(void) {
    /* Mock GPIO port structure for testing */
    GPIO_Registers_t mock_GPIO_Reg;
    mock_GPIO_Reg.IDR = 0b00000000; // Assuming GPIO_pin 5 is reset in the IDR

    /* Initialize GPIO port and pin */
    GPIO_Registers_t* GPIO_Base_Reg = &mock_GPIO_Reg;

    void* GPIO_Port = GPIO_Base_Reg; // Use the address of the mock structure

    u8 GPIO_pin = 5;
    u8 GPIO_State;

    /* Call GPIO_getPinValue */
    GPIO_ErrorStatus_t result = GPIO_getPinValue(GPIO_Port, GPIO_pin, &GPIO_State);

    /* Check if the function returns GPIO_OK */
    TEST_ASSERT_EQUAL_INT(GPIO_OK, result);

    /* Check if GPIO_State is set to GPIO_STATE_RESET */
    TEST_ASSERT_EQUAL_INT(GPIO_STATE_RESET, GPIO_State);
}

#if 0
void test_GPIO_getPinValue_nullPointer(void) {
    /* Mock GPIO port structure for testing */
    GPIO_Registers_t mock_GPIO_Reg;

    /* Initialize GPIO port and pin */
    GPIO_Registers_t* GPIO_Base_Reg = &mock_GPIO_Reg;

    void* GPIO_Port = GPIO_Base_Reg; // Use the address of the mock structure

    u8 GPIO_pin = 3;
    u8 GPIO_State;

    /* Call GPIO_getPinValue with a null pointer */
    GPIO_ErrorStatus_t result = GPIO_getPinValue(GPIO_Port, GPIO_pin, NULL_PTR);

    /* Check if the function returns GPIO_NULLPTR */
    TEST_ASSERT_EQUAL_INT(GPIO_NULLPTR, result);
}
#endif

void test_GPIO_getPinValue_invalidPin(void) {
    /* Mock GPIO port structure for testing */
    GPIO_Registers_t mock_GPIO_Reg;

    /* Initialize GPIO port and an invalid pin */
    GPIO_Registers_t* GPIO_Base_Reg = &mock_GPIO_Reg;

    void* GPIO_Port = GPIO_Base_Reg; // Use the address of the mock structure

    u8 invalid_pin = 20; // Choose an invalid pin number
    u8 GPIO_State;

    /* Call GPIO_getPinValue with an invalid pin */
    GPIO_ErrorStatus_t result = GPIO_getPinValue(GPIO_Port, invalid_pin, &GPIO_State);

    /* Check if the function returns GPIO_InvalidPin */
    TEST_ASSERT_EQUAL_INT(GPIO_InvalidPin, result);
}

void setUp()
{

}

void tearDown()
{

}


/*int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_GPIO_Init_InvalidSpeed);
    RUN_TEST(test_GPIO_Init_InvalidMode);
    RUN_TEST(test_GPIO_Init_ValidCfg);
    RUN_TEST(test_GPIO_Init_InvalidPin);
    RUN_TEST(test_GPIO_setPinValue_validSetState);
    RUN_TEST(test_GPIO_setPinValue_validResetState);
    RUN_TEST(test_GPIO_setPinValue_nullPointer);
    RUN_TEST(test_GPIO_setPinValue_invalidPin);
    RUN_TEST(test_GPIO_setPinValue_invalidState);
    RUN_TEST(test_GPIO_getPinValue_validStateSet);
    RUN_TEST(test_GPIO_getPinValue_validStateReset);
    RUN_TEST(test_GPIO_getPinValue_nullPointer);
    RUN_TEST(test_GPIO_getPinValue_invalidPin);

    
    UNITY_END();
    
    return 0;   
}*/



#endif // TEST
