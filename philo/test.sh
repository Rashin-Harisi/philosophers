#!/bin/bash

BIN="./philo"
OUT_DIR="philo_test_results"
SUMMARY="$OUT_DIR/summary.log"

mkdir -p "$OUT_DIR"
rm -f "$OUT_DIR"/*.log

make re > "$OUT_DIR/build.log" 2>&1

if [ ! -x "$BIN" ]; then
	echo "❌ Build failed. Check $OUT_DIR/build.log"
	exit 1
fi

echo "========== PHILO TEST SUMMARY ==========" > "$SUMMARY"
echo "Date: $(date)" >> "$SUMMARY"
echo "" >> "$SUMMARY"

run_test()
{
	NAME="$1"
	CMD="$2"
	TIMEOUT="$3"
	EXPECT_DEATH="$4"
	EXPECT_FINISH="$5"

	LOG="$OUT_DIR/${NAME}.log"

	echo "------ $NAME ------" >> "$SUMMARY"
	echo "Command: $CMD" >> "$SUMMARY"

	timeout "$TIMEOUT" $CMD > "$LOG" 2>&1
	RET=$?

	DEATH_COUNT=$(grep -c "died" "$LOG")
	LAST_LINE=$(tail -n 1 "$LOG")

	STATUS="PASS"

	if [ "$EXPECT_DEATH" = "yes" ] && [ "$DEATH_COUNT" -ne 1 ]; then
		STATUS="FAIL"
	fi

	if [ "$EXPECT_DEATH" = "no" ] && [ "$DEATH_COUNT" -ne 0 ]; then
		STATUS="FAIL"
	fi

	if [ "$EXPECT_FINISH" = "yes" ] && [ "$RET" -eq 124 ]; then
		STATUS="FAIL"
	fi

	if [ "$EXPECT_FINISH" = "no" ] && [ "$RET" -ne 124 ]; then
		STATUS="FAIL"
	fi

	echo "Result: $STATUS" >> "$SUMMARY"
	echo "Exit code: $RET" >> "$SUMMARY"
	echo "Death count: $DEATH_COUNT" >> "$SUMMARY"
	echo "Last line: $LAST_LINE" >> "$SUMMARY"
	echo "Log file: $LOG" >> "$SUMMARY"
	echo "" >> "$SUMMARY"

	echo "$STATUS - $NAME"
}

run_test "single_philo" "$BIN 1 800 200 200" "3s" "yes" "yes"
run_test "normal_5" "$BIN 5 800 200 200" "5s" "no" "no"
run_test "normal_4_tight" "$BIN 4 410 200 200" "5s" "no" "no"
run_test "death_case" "$BIN 4 310 200 100" "3s" "yes" "yes"
run_test "must_eat_5" "$BIN 5 800 200 200 7" "10s" "no" "yes"
run_test "stress_200" "$BIN 200 800 200 200" "10s" "no" "no"
run_test "stress_200_must_eat" "$BIN 200 800 200 200 3" "20s" "no" "yes"

echo ""
echo "Summary saved in: $SUMMARY"
echo "Full logs are in: $OUT_DIR/"