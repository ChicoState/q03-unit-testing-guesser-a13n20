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
	Guesser guesser("longer");
	bool actual = guesser.match("short");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, distance_start_same_longer)
{
	Guesser guesser("long");
	bool actual = guesser.match("longer");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, distance_start_same_shorter)
{
	Guesser guesser("longer");
	bool actual = guesser.match("long");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, match_lock_after_distance_over_2_length)
{
	Guesser guesser("long");
	guesser.match("longerr");
	bool actual = guesser.match("long");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, match_lock_after_distance_over_2_letters)
{
	Guesser guesser("match");
	guesser.match("isnot");
	bool actual = guesser.match("match");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, match_one_difference)
{
	Guesser guesser("match");
	bool actual = guesser.match("catch");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, match_one_difference_continue)
{
	Guesser guesser("match");
	guesser.match("catch");
	bool actual = guesser.match("match");
	ASSERT_EQ(true, actual);
}

TEST(GuesserTest, match_two_difference_continue)
{
	Guesser guesser("match");
	guesser.match("mirch");
	bool actual = guesser.match("match");
	ASSERT_EQ(true, actual);
}

TEST(GuesserTest, match_three_difference_continue)
{
	Guesser guesser("match");
	guesser.match("birch");
	bool actual = guesser.match("match");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, match_out_of_tries_continue)
{
	Guesser guesser("match");
	guesser.match("catch");
	guesser.match("latch");
	guesser.match("hatch");
	bool actual = guesser.match("match");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, remaining_one_try)
{
	Guesser guesser("match");
	guesser.match("catch");
	int actual = guesser.remaining();
	ASSERT_EQ(2, actual);
}

TEST(GuesserTest, remiaining_two_tries)
{
	Guesser guesser("match");
	guesser.match("catch");
	guesser.match("latch");
	int actual = guesser.remaining();
	ASSERT_EQ(1, actual);
}

TEST(GuesserTest, remiaining_out_of_tries)
{
	Guesser guesser("match");
	guesser.match("catch");
	guesser.match("latch");
	guesser.match("hatch");
	int actual = guesser.remaining();
	ASSERT_EQ(0, actual);
}

TEST(GuesserTest, remaining_one_try_then_succeed)
{
	Guesser guesser("match");
	guesser.match("catch");
	guesser.match("match");
	int actual = guesser.remaining();
	ASSERT_EQ(3, actual);
}

TEST(GuesserTest, match_all_different)
{
	Guesser guesser("match");
	bool actual = guesser.match("hctam");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, match_all_different_try_again)
{
	Guesser guesser("match");
	guesser.match("hctam");
	bool actual = guesser.match("match");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, match_all_different_length)
{
	Guesser guesser("match");
	guesser.match("hctamoijfrr");
	bool actual = guesser.match("match");
	ASSERT_EQ(false, actual);
}

TEST(GuesserTest, match_empty_with_empty)
{
	Guesser guesser("");
	bool actual = guesser.match("");
	ASSERT_EQ(true, actual);
}

TEST(GuesserTest, constructor_secret_too_long_tries_wrong)
{
	Guesser guesser("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
	bool actual = guesser.match("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
	ASSERT_EQ(false, actual);
}


TEST(GuesserTest, constructor_secret_too_long_tries_correct)
{
	Guesser guesser("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
	bool actual = guesser.match("abcdefghijklmnopqrstuvwxyzabcdef");
	ASSERT_EQ(true, actual);
}