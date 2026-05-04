#!/bin/bash

OUT="philo_bonus_tests.log"
BIN="./philo_bonus"

make re

echo "DATE: $(date)" > "$OUT"
echo "" >> "$OUT"

run_test()
{
	NAME="$1"
	CMD="$2"
	LIMIT="$3"
	EXPECT="$4"

	echo "----------------------------" >> "$OUT"
	echo "TEST: $NAME" >> "$OUT"
	echo "Command: $CMD" >> "$OUT"
	echo "Expected: $EXPECT" >> "$OUT"
	echo "-----------------------------" >> "$OUT"

	timeout "$LIMIT" bash -c "$CMD" > tmp_bonus.log 2>&1
	STATUS=$?

	cat tmp_bonus.log >> "$OUT"

	if [ "$EXPECT" = "death" ]; then
		if grep -q "died" tmp_bonus.log; then
			echo "RESULT: PASS" >> "$OUT"
		else
			echo "RESULT: FAIL - expected death" >> "$OUT"
		fi
	elif [ "$EXPECT" = "no_death" ]; then
		if grep -q "died" tmp_bonus.log; then
			echo "RESULT: FAIL - unexpected death" >> "$OUT"
		else
			echo "RESULT: PASS" >> "$OUT"
		fi
	elif [ "$EXPECT" = "finish" ]; then
		if grep -q "died" tmp_bonus.log; then
			echo "RESULT: FAIL - died before finishing" >> "$OUT"
		elif [ "$STATUS" -eq 124 ]; then
			echo "RESULT: FAIL - timeout, program did not finish" >> "$OUT"
		else
			echo "RESULT: PASS" >> "$OUT"
		fi
	elif [ "$EXPECT" = "invalid" ]; then
		if [ "$STATUS" -eq 124 ]; then
			echo "RESULT: FAIL - invalid input caused timeout" >> "$OUT"
		else
			echo "RESULT: PASS" >> "$OUT"
		fi
	fi

	echo "" >> "$OUT"
	rm -f tmp_bonus.log
}

run_test "One philosopher should die" "$BIN 1 800 200 200" 3 "death"
run_test "Must eat 2 times and finish without death" "$BIN 3 800 200 200 2" 5 "finish"
run_test "5 philosophers should not die early" "$BIN 5 800 200 200" 8 "no_death"
run_test "4 philosophers stable timing" "$BIN 4 410 200 200" 8 "no_death"
run_test "Death expected because eat > die" "$BIN 4 200 210 100" 3 "death"
run_test "Must eat 7 times and finish" "$BIN 5 800 200 200 7" 10 "finish"

run_test "Invalid zero philosophers" "$BIN 0 800 200 200" 2 "invalid"
run_test "Invalid negative philosophers" "$BIN -1 800 200 200" 2 "invalid"
run_test "Invalid non-number" "$BIN abc 800 200 200" 2 "invalid"
run_test "Invalid zero time" "$BIN 5 0 200 200" 2 "invalid"
run_test "Invalid too many philosophers" "$BIN 201 800 200 200" 2 "invalid"

echo "Done. Results saved in $OUT"