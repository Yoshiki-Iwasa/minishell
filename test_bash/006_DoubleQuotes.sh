PS1=' $'
echo "006_DoubleQuotes"
echo ""

echo "minishell\$ touch a.txt"
touch a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat \"a.txt\""
cat "a.txt"
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat \" a.txt\""
cat " a.txt"
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat \"a.txt;\""
cat "a.txt;"
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ rm \"a.txt\""
rm "a.txt"
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat \"\""
cat ""
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat \"\\\"\""
cat "\""
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat \"\\\$\""
cat "\$"
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ touch \"\\\"\\\"\""
touch "\"\""
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat \"\\\"\\\"\""
cat "\"\""
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ rm \"\\\"\\\"\""
rm "\"\""
echo "minishell\$ "
echo "minishell\$ "