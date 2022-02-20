#include "unity.h"

#include "SSD1306_oled.h"
#include "buffer_oled_expect.h"
#include "string.h"


void setUp(void)
{
    memset(buffer_oled, 0xFF, SSD1306_BUF_SIZE);

}

void tearDown(void)
{
}


void test_wrtie_to_buffer_at_pos_0_0_height_8pt(void)
{
    SSD1306_write_to_buffer(picture_8pt, SSD1306_LCDWIDTH, 8, 0, 0, NORMAL);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(posX_0_posY_0_8pt, buffer_oled, SSD1306_BUF_SIZE);
}

void test_wrtie_to_buffer_at_pos_1_0_height_8pt(void)
{
    SSD1306_write_to_buffer(picture_8pt, SSD1306_LCDWIDTH, 8, 0, 1, NORMAL);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(posX_0_posY_1_8pt, buffer_oled, SSD1306_BUF_SIZE);
}

void test_wrtie_to_buffer_at_pos_7_0_height_8pt(void)
{
    SSD1306_write_to_buffer(picture_8pt, SSD1306_LCDWIDTH, 8, 0, 7, NORMAL);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(posX_0_posY_7_8pt, buffer_oled, SSD1306_BUF_SIZE);
}

void test_wrtie_to_buffer_at_pos_0_0_height_16pt(void)
{
    SSD1306_write_to_buffer(picture_16pt, SSD1306_LCDWIDTH, 16, 0, 0, NORMAL);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(posX_0_posY_0_16pt, buffer_oled, SSD1306_BUF_SIZE);
}

void test_wrtie_to_buffer_at_pos_1_0_height_16pt(void)
{
    SSD1306_write_to_buffer(picture_16pt, SSD1306_LCDWIDTH, 16, 0, 1, NORMAL);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(posX_0_posY_1_16pt, buffer_oled, SSD1306_BUF_SIZE);
}

void test_wrtie_to_buffer_at_pos_7_0_height_16pt(void)
{
    SSD1306_write_to_buffer(picture_16pt, SSD1306_LCDWIDTH, 16, 0, 7, NORMAL);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(posX_0_posY_7_16pt, buffer_oled, SSD1306_BUF_SIZE);
}

void test_wrtie_to_buffer_at_pos_0_0_height_12pt(void)
{
    SSD1306_write_to_buffer(picture_12pt, SSD1306_LCDWIDTH, 12, 0, 0, NORMAL);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(posX_0_posY_0_12pt, buffer_oled, SSD1306_BUF_SIZE);
}

void test_wrtie_to_buffer_at_pos_1_0_height_12pt(void)
{
    SSD1306_write_to_buffer(picture_12pt, SSD1306_LCDWIDTH, 12, 0, 1, NORMAL);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(posX_0_posY_1_12pt, buffer_oled, SSD1306_BUF_SIZE);
}

void test_wrtie_to_buffer_at_pos_4_0_height_12pt(void)
{
    SSD1306_write_to_buffer(picture_12pt, SSD1306_LCDWIDTH, 12, 0, 4, NORMAL);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(posX_0_posY_4_12pt, buffer_oled, SSD1306_BUF_SIZE);
}

void test_wrtie_to_buffer_at_pos_7_0_height_12pt(void)
{
    SSD1306_write_to_buffer(picture_12pt, SSD1306_LCDWIDTH, 12, 0, 7, NORMAL);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(posX_0_posY_7_12pt, buffer_oled, SSD1306_BUF_SIZE);
}

void test_wrtie_to_buffer_at_pos_minus1_0_height_8pt(void)
{
    SSD1306_write_to_buffer(picture_8pt, SSD1306_LCDWIDTH, 8, 0, -1, NORMAL);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(posX_0_posY_minus1_8pt, buffer_oled, SSD1306_BUF_SIZE);
}

void test_wrtie_to_buffer_at_pos_minus7_0_height_8pt(void)
{
    SSD1306_write_to_buffer(picture_8pt, SSD1306_LCDWIDTH, 8, 0, -7, NORMAL);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(posX_0_posY_minus7_8pt, buffer_oled, SSD1306_BUF_SIZE);
}

void test_wrtie_to_buffer_at_pos_minus8_0_height_8pt(void)
{
    SSD1306_write_to_buffer(picture_8pt, SSD1306_LCDWIDTH, 8, 0, -8, NORMAL);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(buffer_oled, buffer_oled, SSD1306_BUF_SIZE);
}

void test_wrtie_to_buffer_at_pos_0_minus1_height_8pt(void)
{
    SSD1306_write_to_buffer(picture_8pt, SSD1306_LCDWIDTH, 8, -1, 0, NORMAL);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(posX_minus1_posY_0_8pt, buffer_oled, SSD1306_BUF_SIZE);
}

void test_wrtie_to_buffer_at_pos_60_minus1_height_8pt(void)
{
    SSD1306_write_to_buffer(picture_8pt, SSD1306_LCDWIDTH, 8, -1, 60, NORMAL);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(posX_minus1_posY_60_8pt, buffer_oled, SSD1306_BUF_SIZE);
}

void test_wrtie_to_buffer_at_pos_0_0_inverse_height_8pt(void)
{
    SSD1306_write_to_buffer(picture_8pt, SSD1306_LCDWIDTH, 8, 0, 0, INVERSE);

    TEST_ASSERT_EQUAL_HEX8_ARRAY(posX_0_posY_0_inverse_8pt, buffer_oled, SSD1306_BUF_SIZE);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_wrtie_to_buffer_at_pos_0_0_height_8pt);
    RUN_TEST(test_wrtie_to_buffer_at_pos_7_0_height_8pt);
    RUN_TEST(test_wrtie_to_buffer_at_pos_1_0_height_8pt);
    RUN_TEST(test_wrtie_to_buffer_at_pos_0_0_height_16pt);
    RUN_TEST(test_wrtie_to_buffer_at_pos_1_0_height_16pt);
    RUN_TEST(test_wrtie_to_buffer_at_pos_7_0_height_16pt);
    RUN_TEST(test_wrtie_to_buffer_at_pos_0_0_height_12pt);
    RUN_TEST(test_wrtie_to_buffer_at_pos_1_0_height_12pt);
    RUN_TEST(test_wrtie_to_buffer_at_pos_4_0_height_12pt);
    RUN_TEST(test_wrtie_to_buffer_at_pos_7_0_height_12pt);
    RUN_TEST(test_wrtie_to_buffer_at_pos_minus1_0_height_8pt);
    RUN_TEST(test_wrtie_to_buffer_at_pos_minus7_0_height_8pt);
    RUN_TEST(test_wrtie_to_buffer_at_pos_minus8_0_height_8pt);
    RUN_TEST(test_wrtie_to_buffer_at_pos_0_minus1_height_8pt);
    RUN_TEST(test_wrtie_to_buffer_at_pos_60_minus1_height_8pt);
    RUN_TEST(test_wrtie_to_buffer_at_pos_0_0_inverse_height_8pt);
    

    return UNITY_END();
}