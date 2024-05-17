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
    leaks -atExit -- ./s21_cat $template > s21_cat_test_leak.log
    leak=$(grep -A100000 leaks s21_cat_test_leak.log)
    (( COUNTER_LEAK++ ))
    if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
    then
      (( SUCCESS_LEAK++ )) 
        echo "\033[36m[fail_leak=$FAIL_LEAK|success_leak=$SUCCESS_LEAK|all_leak_tests=$COUNTER_LEAK]" 
        testing_work template
    else
      (( FAIL_LEAK++ ))
        testing_work template
        echo "\033[0m\033[0m\033[31m[fail_leak=$FAIL_LEAK|success_leak=$SUCCESS_LEAK|all_leak_tests=$COUNTER_LEAK]"
    fi
    rm s21_cat_my_work.log
    rm s21_cat_orginal_work.log
    rm s21_cat_test_leak.log
}

testing_work()
{
    ./s21_cat $template > s21_cat_my_work.log
    cat $template > s21_cat_orginal_work.log
    DIFF_RES="$(diff -s s21_cat_my_work.log s21_cat_orginal_work.log)"
    (( COUNTER_WORK++ ))
    if [ "$DIFF_RES" == "Files s21_cat_my_work.log and s21_cat_orginal_work.log are identical" ]
    then
      (( SUCCESS_WORK++ ))
      echo "\033[34m[fail_work=$FAIL_WORK|success_work=$SUCCESS_WORK|all_work_tests=$COUNTER_WORK]\033[37m cat $template\n"
    else
      (( FAIL_WORK++ ))
      echo "\033[0m\033[0m\033[31m[fail_work=$FAIL_WORK|success_work=$SUCCESS_WORK|all_work_tests=$COUNTER_WORK]\033[37m cat $template\n"
    fi
}

for var1 in b e n s t v
do
    for i in "VAR cat_1.txt" "VAR cat_2.txt" "VAR cat_3.txt" "VAR cat_4.txt" "VAR cat_5.txt" "VAR cat_6.txt"
    do
        var="-$var1"
        testing_leak $i
    done
done

var="-"

echo "\033[31mПАМЯТЬ УТЕКЛА(Кол-во раз): $FAIL_LEAK\033[0m"
echo "\033[32mПАМЯТЬ НЕ УТЕКЛА(Кол-во раз): $SUCCESS_LEAK\033[0m"
echo "\033[31mПРОВАЛЕННЫХ ТЕСТОВ: $FAIL_WORK\033[0m"
echo "\033[32mУСПЕШНЫХ ТЕСТОВ: $SUCCESS_WORK\033[0m"