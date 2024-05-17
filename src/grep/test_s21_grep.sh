#!/bin/bash

SUCCESS_LEAK=0
SUCCESS_WORK=0
FAIL_LEAK=0
FAIL_WORK=0
COUNTER_LEAK=0
COUNTER_WORK=0
DIFF_RES=""

testing_leak()
{
    template=$(echo $@ | sed "s/VAR/$var/")
    leaks -atExit -- ./s21_grep $template > s21_grep_test_leak.log
    leak=$(grep -A100000 leaks s21_grep_test_leak.log)
    (( COUNTER_LEAK++ ))
    if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
    then
      (( SUCCESS_LEAK++ ))
        echo "\033[36m[fail_leak=$FAIL_LEAK|success_leak=$SUCCESS_LEAK|all_leak_tests=$COUNTER_LEAK]" 
        testing_work template
    else
      (( FAIL_LEAK++ ))
        echo "\033[0m\033[0m\033[31m[fail_leak=$FAIL_LEAK|success_leak=$SUCCESS_LEAK|all_leak_tests=$COUNTER_LEAK]" 
        testing_work template
    fi
    rm s21_grep_my_work.log
    rm s21_grep_orginal_work.log
    rm s21_grep_test_leak.log
}

testing_work()
{
    ./s21_grep $template > s21_grep_my_work.log
    grep $template > s21_grep_orginal_work.log
    DIFF_RES="$(diff -s s21_grep_my_work.log s21_grep_orginal_work.log)"
    (( COUNTER_WORK++ ))
    if [ "$DIFF_RES" == "Files s21_grep_my_work.log and s21_grep_orginal_work.log are identical" ]
    then
      (( SUCCESS_WORK++ ))
        echo "\033[34m[fail_work=$FAIL_WORK|success_work=$SUCCESS_WORK|all_work_tests=$COUNTER_WORK]\033[37m grep $template\n"
    else
      (( FAIL_WORK++ ))
        echo "\033[0m\033[0m\033[31m[fail_work=$FAIL_WORK|success_work=$SUCCESS_WORK|all_work_tests=$COUNTER_WORK]\033[37m grep $template\n"
    fi
}

var="simple"
testing_leak "VAR grep_1.txt grep_2.txt"

var="-e simple"
testing_leak "VAR grep_1.txt"

var="-esimple"
testing_leak "VAR grep_1.txt"

var="-f grep_pattern.txt"
testing_leak "VAR grep_1.txt"

var="-fgrep_pattern.txt"
testing_leak "VAR grep_1.txt"

var=""
testing_leak ""

var="-e simple -e hard"
testing_leak "VAR grep_1.txt grep_2.txt grep_3.txt"

for var1 in i v c l n h s o
do
    for i in "VAR simple grep_1.txt" "VAR simple grep_2.txt" "VAR simple grep_3.txt"
    do
        var="-$var1"
        testing_leak $i
    done
done

echo "\033[31mПАМЯТЬ УТЕКЛА(Кол-во раз): $FAIL_LEAK\033[0m"
echo "\033[32mПАМЯТЬ НЕ УТЕКЛА(Кол-во раз): $SUCCESS_LEAK\033[0m"
echo "\033[31mПРОВАЛЕННЫХ ТЕСТОВ: $FAIL_WORK\033[0m"
echo "\033[32mУСПЕШНЫХ ТЕСТОВ: $SUCCESS_WORK\033[0m"