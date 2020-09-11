PS1='$ '
echo "008_export"
echo ""

echo "minishell\$ export testenv1=TEST1"
export testenv1=TEST1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ env | grep testenv1"
env | grep testenv1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ testenv1=REPLACE_TEST1"
testenv1=REPLACE_TEST1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ env | grep testenv1"
env | grep testenv1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ testenv1="
testenv1=
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ env | grep testenv1"
env | grep testenv1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ export testenv2"
export testenv2
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ env | grep testenv2"
env | grep testenv2
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ export testenv3="
export testenv3=
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ env | grep testenv3"
env | grep testenv3
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ testenv2=TEST2"
testenv2=TEST2
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ export testenv2"
export testenv2
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ env | grep testenv2"
env | grep testenv2
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ testenv:=TEST"
testenv:=TEST
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ testenv1= pwd"
testenv1= pwd
echo "minishell\$ "
echo "minishell\$ "