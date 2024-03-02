#ifdef TEST

#include "unity.h"
#include "mock_GPIO.h"
#include "Switch.h"
#define Switch_Test 0

SWITCH_Cfg_t Switches[_SWITCH_NUM]=
{
    [Switch_Test]={
        .pin = GPIO_PIN_5,
        .port = GPIO_PORT_A,
        .dir = SWITCH_PULL_DOWN,
    }
};

void setUp(void)
{
}

void tearDown(void)
{
}

GPIO_ErrorStatus_t GPIO_Init_CallbackValidConfiguration(GPIO_Pin_t* gpioPin, int cmock_num_calls) {
    /*Check that gpioPin's fields match what you expect*/ 
    /*It Must Match What I written in my mocked Switch above*/
    TEST_ASSERT_EQUAL(Switches[Switch_Test].pin, gpioPin->GPIO_Pin);
    TEST_ASSERT_EQUAL(Switches[Switch_Test].port, gpioPin->GPIO_Port);
    TEST_ASSERT_EQUAL(Switches[Switch_Test].dir, gpioPin->GPIO_Mode);
    return GPIO_OK;
}

void test_SWITCH_Init_ValidConfiguration(void) {

    GPIO_Init_StubWithCallback(GPIO_Init_CallbackValidConfiguration);

    SWITCH_ErrorStatus_t result = SWITCH_Init();

    TEST_ASSERT_EQUAL(SWITCH_OK, result);
}

void test_SWITCH_Init_InvalidConfiguration(void) {

    Switches[Switch_Test].dir = 0xFF;

    SWITCH_ErrorStatus_t result = SWITCH_Init();
    TEST_ASSERT_EQUAL(SWITCH_InvalidDir, result);

    Switches[Switch_Test].dir = SWITCH_PULL_UP;
}

void test_SWITCH_getState_InvalidName(void) {
    u8 dummy_state;
    SWITCH_ErrorStatus_t result = SWITCH_getState(_SWITCH_NUM, &dummy_state); // Using _SWITCH_NUM as invalid index

    TEST_ASSERT_EQUAL(SWITCH_InvalidName, result);
}

void test_SWITCH_getState_NullPtr(void) {
    SWITCH_ErrorStatus_t result = SWITCH_getState(Switch_Test, NULL_PTR); // Null pointer for state

    TEST_ASSERT_EQUAL(SWITCH_NullPtr, result);
}
GPIO_ErrorStatus_t GPIO_getPinValue_CallbackStateReset(void* GPIO_Port, u8 GPIO_pin, u8* GPIO_State, int cmock_num_calls) {
    /*Check that gpioPin's fields match what you expect*/ 
    /*It Must Match What I written in my mocked Switch above*/
    *GPIO_State = GPIO_STATE_RESET;
    TEST_ASSERT_EQUAL(Switches[Switch_Test].pin, GPIO_pin);
    TEST_ASSERT_EQUAL(Switches[Switch_Test].port, GPIO_Port);
    return GPIO_OK;
}
GPIO_ErrorStatus_t GPIO_getPinValue_CallbackStateSet(void* GPIO_Port, u8 GPIO_pin, u8* GPIO_State, int cmock_num_calls) {

    *GPIO_State = GPIO_STATE_SET;
    TEST_ASSERT_EQUAL(Switches[Switch_Test].pin, GPIO_pin);
    TEST_ASSERT_EQUAL(Switches[Switch_Test].port, GPIO_Port);
    return GPIO_OK;
}

void test_SWITCH_getState_ValidSwitchLowStatePullUp(void) 
{
    Switches[Switch_Test].dir = SWITCH_PULL_UP;
    u8 actualSwitchState;
    GPIO_getPinValue_StubWithCallback(GPIO_getPinValue_CallbackStateReset);

    SWITCH_ErrorStatus_t result = SWITCH_getState(Switch_Test, &actualSwitchState);

    TEST_ASSERT_EQUAL(SWITCH_OK, result);
    TEST_ASSERT_EQUAL(SWITCH_PRESSED, actualSwitchState); 
}
void test_SWITCH_getState_ValidSwitchHighStatePullUp(void) 
{
    Switches[Switch_Test].dir = SWITCH_PULL_UP;
    u8 actualSwitchState;
    GPIO_getPinValue_StubWithCallback(GPIO_getPinValue_CallbackStateSet);

    SWITCH_ErrorStatus_t result = SWITCH_getState(Switch_Test, &actualSwitchState);

    TEST_ASSERT_EQUAL(SWITCH_OK, result);
    TEST_ASSERT_EQUAL(SWITCH_RELEASED, actualSwitchState); 
}
void test_SWITCH_getState_ValidSwitchLowStatePullDown(void) 
{
    Switches[Switch_Test].dir = SWITCH_PULL_DOWN;
    u8 actualSwitchState;
    GPIO_getPinValue_StubWithCallback(GPIO_getPinValue_CallbackStateReset);

    SWITCH_ErrorStatus_t result = SWITCH_getState(Switch_Test, &actualSwitchState);

    TEST_ASSERT_EQUAL(SWITCH_OK, result);
    TEST_ASSERT_EQUAL(SWITCH_RELEASED, actualSwitchState); 
}
void test_SWITCH_getState_ValidSwitchHighStatePullDown(void) 
{
    Switches[Switch_Test].dir = SWITCH_PULL_DOWN;
    u8 actualSwitchState;
    GPIO_getPinValue_StubWithCallback(GPIO_getPinValue_CallbackStateSet);

    SWITCH_ErrorStatus_t result = SWITCH_getState(Switch_Test, &actualSwitchState);

    TEST_ASSERT_EQUAL(SWITCH_OK, result);
    TEST_ASSERT_EQUAL(SWITCH_PRESSED, actualSwitchState); 
}
#endif // TEST
