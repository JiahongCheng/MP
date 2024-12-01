// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

TEST_CASE("horizontal") {
	std::vector<std::vector<char>> puzzle{{'h', 'o', 'o', 'o', 'o'},
                                        {'o', 'a', 'o', 'l', 'h'},
                                        {'l', 'a', 't', 'a', 'o'},
                                        {'l', 'o', 't', 'o', 'o'},
                                        {'h', 'e', 'l', 'l', 'o'}};

	std::vector<CharPositions> key {CharPositions{'h', 4, 0}, 
									CharPositions{'e', 4, 1}, 
									CharPositions{'l', 4, 2}, 
									CharPositions{'l', 4, 3}, 
									CharPositions{'o', 4, 4}};

  	WordSearchSolver wss(puzzle);
	SECTION("correct search"){
		WordLocation first = wss.FindWord("hello", CheckDirection::kHorizontal);
		REQUIRE(first.word == "hello");
		REQUIRE(first.char_positions[0].row == 4);
		REQUIRE(first.char_positions[0].col == 0);
		REQUIRE(first.char_positions[1].row == 4);
		REQUIRE(first.char_positions[1].col == 1);
		WordLocation second = wss.FindWord("hello");
		REQUIRE(second.word == "hello");
	}
	SECTION("no match"){
		WordLocation location = wss.FindWord("heloo", CheckDirection::kHorizontal);
		REQUIRE(location.word.empty());
	}
	SECTION("out of boud") {
		WordLocation location = wss.FindWord("oooooooo", CheckDirection::kHorizontal);
		REQUIRE(location.word.empty());
	}
}

TEST_CASE("Vertical") {
  std::vector<std::vector<char>> puzzle{{'h', 'o', 'o', 'o', 'o'},
                                        {'o', 'a', 'o', 'l', 'h'},
                                        {'l', 'a', 't', 'a', 'o'},
                                        {'l', 'o', 't', 'o', 'o'},
                                        {'h', 'e', 'l', 'l', 'o'}};
  WordSearchSolver wss(puzzle);
	SECTION("correct search"){
		WordLocation first = wss.FindWord("hollh", CheckDirection::kVertical);
		REQUIRE(first.word == "hollh");
		WordLocation second = wss.FindWord("holl");
		REQUIRE(second.word == "holl");
		WordLocation third = wss.FindWord("hollh", CheckDirection::kHorizontal);
		REQUIRE(third.word.empty());
	}
	SECTION("no match"){
		WordLocation location = wss.FindWord("hollo", CheckDirection::kVertical);
		REQUIRE(location.word.empty());
	}
}

TEST_CASE("LeftDiag") {
  std::vector<std::vector<char>> puzzle{{'o', 'o', 'o', 'o', 'o'},
                                        {'o', 'a', 'o', 'l', 'h'},
                                        {'l', 'a', 't', 'a', 'o'},
                                        {'l', 'o', 't', 'o', 'o'},
                                        {'h', 'e', 'l', 'l', 'o'}};
  WordSearchSolver wss(puzzle);
	SECTION("correct search"){
		WordLocation first = wss.FindWord("hat", CheckDirection::kLeftDiag);
		REQUIRE(first.word == "hat");
		WordLocation second = wss.FindWord("hat");
		REQUIRE(second.word == "hat");
	}
	SECTION("no match"){
		WordLocation location = wss.FindWord("hot", CheckDirection::kLeftDiag);
		REQUIRE(location.word.empty());
	}
}


TEST_CASE("RightDiag") {
  std::vector<std::vector<char>> puzzle{{'h', 'o', 'o', 'o', 'o'},
                                        {'o', 'a', 'o', 'l', 'o'},
                                        {'l', 'a', 't', 'a', 'o'},
                                        {'l', 'o', 't', 'o', 'o'},
                                        {'h', 'e', 'l', 'l', 'o'}};
  WordSearchSolver wss(puzzle);
	SECTION("correct search"){
		WordLocation first = wss.FindWord("hat", CheckDirection::kRightDiag);
		REQUIRE(first.word == "hat");
		WordLocation second = wss.FindWord("hat");
		REQUIRE(second.word == "hat");
	}
	SECTION("no match"){
		WordLocation location = wss.FindWord("het", CheckDirection::kRightDiag);
		REQUIRE(location.word.empty());
	}
}

TEST_CASE("One col") {
  std::vector<std::vector<char>> puzzle{{'o'},
                                        {'o'},
                                        {'o'},
                                        {'o'},
                                        {'o'},
										{'o'},
										{'o'},
										{'o'}};
  WordSearchSolver wss(puzzle);
	SECTION("correct search"){
		REQUIRE(wss.FindWord("ooo").word == "ooo");
		REQUIRE(wss.FindWord("ooo", CheckDirection::kVertical).word == "ooo");
	}
	SECTION("no match"){
		WordLocation location = wss.FindWord("holl", CheckDirection::kVertical);
		REQUIRE(location.word.empty());
	}
}

TEST_CASE("One row") {
  std::vector<std::vector<char>> puzzle{{'a', 'b', 'c', 'd', 'e', 'f'}};

  WordSearchSolver wss(puzzle);
	SECTION("correct search"){
		REQUIRE(wss.FindWord("e").word == "e");
		REQUIRE(wss.FindWord("e", CheckDirection::kHorizontal).word == "e");
		REQUIRE(wss.FindWord("e", CheckDirection::kVertical).word == "e");
		REQUIRE(wss.FindWord("e", CheckDirection::kRightDiag).word == "e");
		REQUIRE(wss.FindWord("e", CheckDirection::kLeftDiag).word == "e");
	}
}


TEST_CASE("Out of Bound") {
  std::vector<std::vector<char>> puzzle{{'h', 'o', 'o', 'o', 'o'},
                                        {'o', 'a', 'o', 'l', 'o'},
                                        {'l', 'a', 't', 'a', 'o'},
                                        {'l', 'o', 't', 'o', 'o'},
                                        {'h', 'e', 'l', 'l', 'o'}};
  WordSearchSolver wss(puzzle);
	SECTION("out of bound"){
		WordLocation first = wss.FindWord("helloo", CheckDirection::kHorizontal);
		REQUIRE(first.word.empty());
		WordLocation second = wss.FindWord("helloo");
		REQUIRE(second.word.empty());
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////