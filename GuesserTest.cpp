/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

/* Example test
TEST(GuesserTest, smoke_test)
{
    ASSERT_EQ( 1+1, 2 );
}
*/

TEST(GuesserTest, distance_equal_inputs)
{
	Guesser guesser("secret");
	bool actual = guesser.match("secret");
	ASSERT_EQ(true, actual);
}

TEST(GuesserTest, distance_guess_longer)
{
	Guesser guesser("short");
	bool actual = guesser.match("longer");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, distance_guess_shorter)
{
	
}