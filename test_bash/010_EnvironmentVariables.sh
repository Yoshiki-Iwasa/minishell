PS1='$ '
echo "010_EnvironmentVariables"
echo ""

echo "minishell\$ testenv1=TEST1"
testenv1=TEST1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ env | grep testenv1"
env | grep testenv1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ export testenv1"
export testenv1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ env | grep testenv1"
env | grep testenv1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ export testenv2=TEST2"
export testenv2=TEST2
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ env | grep testenv2"
env | grep testenv2
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \$testenv1"
echo $testenv1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \$testenv2"
echo $testenv2
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \$testenv1\$testenv2"
echo $testenv1$testenv2
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \$testenv1 \$testenv2"
echo $testenv1 $testenv2
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \"\$testenv1\""
echo "$testenv1"
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \"\\\$testenv1\""
echo "\$testenv1"
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ export testenv1=TEST1"
export testenv1=TEST1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ export testenv1=\$testenv1:add"
export testenv1=$testenv1:add
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ env | grep testenv1"
env | grep testenv1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ testenv1=\\\$value"
testenv1=\$value
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \$testenv1"
echo $testenv1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ testenv1=\$value"
testenv1=$value
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \$testenv1"
echo $testenv1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ testenv1=TEST1"
testenv1=TEST1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ testenv1= pwd"
testenv1= pwd
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \$testenv1"
echo $testenv1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo test\$ test"
echo test$ test
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ test\$ test"
test\$ test
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ \$"
$
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \$"
echo $
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \"$ \""
echo "$ "
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ testenv3=TEST"
testenv3=TEST
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \"\$testenv3\"_after"
echo "$testenv3"_after
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \$testenv3_after"
echo $testenv3_after
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \${testenv3}_after"
echo ${testenv3}_after
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo {\$testenv3}"
echo {$testenv3}
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo before{\$testenv3}after"
echo before{$testenv3}after
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo before{testenv3}after"
echo before{testenv3}after
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo {}"
echo {}
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \${testenv3}{\$testenv3}\$testenv3"
echo ${testenv3}{$testenv3}$testenv3
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ TEST=ABCD"
TEST=ABCD
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \"{\$TEST}\${TEST}\$TEST\" {\$TEST}\${TEST}\$TEST"
echo "{$TEST}${TEST}$TEST" {$TEST}${TEST}$TEST
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \"{\$TEST}\${TEST}{\$TEST}\" {\$TEST}\${TEST}{\$TEST}"
echo "{$TEST}${TEST}{$TEST}" {$TEST}${TEST}{$TEST}
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \"{\$TEST}\${TEST}\$TEST\"{\$TEST}\${TEST}\$TEST"
echo "{$TEST}${TEST}$TEST"{$TEST}${TEST}$TEST
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \"k\\\${USER} k\""
echo "k\${USER} k"
echo "minishell\$ "
echo "minishell\$ "

