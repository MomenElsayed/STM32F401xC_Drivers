#ifdef TEST

#include "unity.h"
#include "mock_GPIO.h"
#include "LED.h"

LED_Cfg_t LEDS[_LEDS_NUM];

void setUp(void)
{
}

void tearDown(void)
{
}

void test_LED_Init_ValidParameters(void)
{
    GPIO_Pin_t expectedLed;
    expectedLed.GPIO_Mode = GPIO_MODE_OUT_PP;
    expectedLed.GPIO_Speed = GPIO_SPEED_MED;
    expectedLed.GPIO_Pin = LEDS[0].pin;
    expectedLed.GPIO_Port = LEDS[0].port;
    GPIO_Init_ExpectAndReturn(&expectedLed,GPIO_OK);
    TEST_ASSERT_EQUAL(LED_OK, LED_Init());
}

void test_LED_Init_InvalidDirection(void)
{
    /*Modify LEDS array to contain an invalid direction*/ 
    LEDS[0].dir = 0x02;

    /*No expectations for GPIO_Init as LED_Init should return an error early*/ 
    TEST_ASSERT_EQUAL(LED_InvalidDir, LED_Init());

    /*Reset LEDS array to its original state*/
    LEDS[0].dir = LED_DIR_FORWARD;
}

void test_LED_setState_ValidParameters(void)
{
    LEDS[0].dir = LED_DIR_FORWARD;
    GPIO_setPinValue_ExpectAndReturn(LEDS[0].port, LEDS[0].pin, 1, GPIO_OK);
    TEST_ASSERT_EQUAL(LED_OK, LED_setState(0, LED_STATE_ON));
    
    // Verify that GPIO_setPinValue was called with the expected arguments
    mock_GPIO_Verify();
}

void test_LED_setState_InvalidLedName(void)
{
    // Call LED_setState with an invalid LED name
    TEST_ASSERT_EQUAL(LED_InvalidLedName, LED_setState(_LEDS_NUM + 1, LED_STATE_OFF));
}

void test_LED_setState_InvalidState(void)
{
    // Call LED_setState with an invalid LED state
    TEST_ASSERT_EQUAL(LED_InvalidState, LED_setState(0, 0xff));
}


#endif // TEST
