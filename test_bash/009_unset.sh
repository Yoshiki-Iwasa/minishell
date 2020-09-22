PS1='$ '
echo "009_unset"
echo ""

echo "minishell\$ export testenv1=TEST1"
export testenv1=TEST1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ env | grep testenv1"
env | grep testenv1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ unset testenv1"
unset testenv1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ env | grep testenv1"
env | grep testenv1
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ unset testenv2"
unset testenv2
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ unset testenv3"
unset testenv3
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ unset"
unset
echo "minishell\$ "
echo "minishell\$ "

