#!/usr/bin/env bash
# Test helper for push_swap. Not part of the graded sources.
# Usage: ./run_tests.sh

set -uo pipefail

cd "$(dirname "$0")"
PUSH=./push_swap
CHECK=./checker_Mac

if [ ! -x "$PUSH" ]; then
	echo "push_swap not found or not executable, running make..."
	make -s
fi
if [ ! -x "$CHECK" ]; then
	echo "checker_Mac not found next to push_swap (expected ./checker_Mac)."
	exit 1
fi

pass=0
fail=0

check_ok()
{
	local desc="$1"
	shift
	local result
	result=$("$PUSH" "$@" | "$CHECK" "$@")
	if [ "$result" = "OK" ]; then
		echo "PASS  $desc"
		pass=$((pass + 1))
	else
		echo "FAIL  $desc -> checker said '$result'"
		fail=$((fail + 1))
	fi
}

check_no_output()
{
	local desc="$1"
	shift
	local out
	out=$("$PUSH" "$@")
	if [ -z "$out" ]; then
		echo "PASS  $desc (no output)"
		pass=$((pass + 1))
	else
		echo "FAIL  $desc -> got output: $out"
		fail=$((fail + 1))
	fi
}

check_error()
{
	local desc="$1"
	shift
	local out
	out=$("$PUSH" "$@" 2>&1 >/dev/null)
	local code=$?
	if [ "$code" -eq 1 ] && [ "$out" = "Error" ]; then
		echo "PASS  $desc (correctly errored)"
		pass=$((pass + 1))
	else
		echo "FAIL  $desc -> exit=$code stderr='$out'"
		fail=$((fail + 1))
	fi
}

echo "== Edge cases =="
check_no_output "no arguments"
check_no_output "single number" 42
check_no_output "already sorted" 1 2 3 4 5
check_ok "two numbers reversed" 2 1
check_ok "already sorted (checker)" 1 2 3

echo
echo "== Expected errors =="
check_error "duplicate values" 1 2 2
check_error "non-numeric" 1 abc 3
check_error "out of int range" 99999999999999
check_error "unknown flag" --bogus 1 2 3

echo
echo "== Optimal sort, n = 0..5 =="
check_no_output "optimal n=0"
for n in 1 2 3 4 5; do
	ARG=$(python3 -c "import random; print(' '.join(str(x) for x in random.sample(range(-100, 100), $n)))")
	check_ok "optimal n=$n ($ARG)" $ARG
done

echo
echo "== Each strategy, forced, same input =="
# NOTE: checker_Mac only understands numbers, not push_swap's --flags, so the
# flag is passed to push_swap alone and only $ARG (the numbers) to the checker.
ARG=$(python3 -c "import random; print(' '.join(str(x) for x in random.sample(range(-5000, 5000), 200)))")
for flag in --simple --medium --complex --adaptive ""; do
	label="${flag:-<default/adaptive>}"
	"$PUSH" $flag $ARG > /tmp/ps_strategy_out.txt
	ops=$(wc -l < /tmp/ps_strategy_out.txt | tr -d ' ')
	result=$(cat /tmp/ps_strategy_out.txt | "$CHECK" $ARG)
	if [ "$result" = "OK" ]; then
		echo "PASS  strategy $label (n=200, $ops ops)"
		pass=$((pass + 1))
	else
		echo "FAIL  strategy $label (n=200, $ops ops) -> checker said '$result'"
		fail=$((fail + 1))
	fi
done

echo
echo "== --bench sanity check (stderr should show strategy + counters) =="
"$PUSH" --bench $ARG > /dev/null

echo
echo "== Adaptive: trigger each disorder branch =="
LOW=$(python3 -c "l=list(range(300)); print(' '.join(map(str, l[150:] + l[:150])))")
echo "-- low disorder (rotation) --"
"$PUSH" --bench $LOW > /dev/null

MED=$(python3 -c "import random; l=list(range(300)); random.shuffle(l); print(' '.join(map(str, l)))")
echo "-- medium disorder (shuffled) --"
"$PUSH" --bench $MED > /dev/null

HIGH=$(python3 -c "print(' '.join(str(x) for x in range(300, 0, -1)))")
echo "-- high disorder (reversed) --"
"$PUSH" --bench $HIGH > /dev/null

echo
echo "== Stress test: large N, timing + op count + checker =="
# NOTE: ft_ra/ft_rra walk the whole linked list to find the tail on every
# call (no tail pointer), so complex_sort's per-bit rotation passes make this
# O(n^2 log n) overall. n=20000 alone took ~37 minutes in one run - raise
# this list only after that rotation cost is fixed.
for n in 100 500 1000 5000; do
	ARG=$(python3 -c "import random; print(' '.join(str(x) for x in random.sample(range(-1000000, 1000000), $n)))")
	start=$(date +%s.%N)
	"$PUSH" $ARG > /tmp/ps_ops.txt
	end=$(date +%s.%N)
	ops=$(wc -l < /tmp/ps_ops.txt | tr -d ' ')
	elapsed=$(python3 -c "print(f'{$end - $start:.2f}')")
	result=$("$PUSH" $ARG | "$CHECK" $ARG)
	echo "n=$n  ops=$ops  time=${elapsed}s  checker=$result"
	if [ "$result" != "OK" ]; then
		fail=$((fail + 1))
	else
		pass=$((pass + 1))
	fi
done

echo
echo "======================================"
echo "Passed: $pass  Failed: $fail"
echo "======================================"
[ "$fail" -eq 0 ]
