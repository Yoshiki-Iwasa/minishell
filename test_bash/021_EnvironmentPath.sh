PS1='$ '
echo "014_EnvironmentPath"
echo ""

echo "minishell\$ date"
date
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \$PATH"
echo $PATH
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ unset PATH"
unset PATH
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \$PATH"
echo $PATH
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ date"
date
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cd /tmp"
cd /tmp
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ /bin/cp /bin/ps ./"
/bin/cp /bin/ps ./
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ /bin/mv ps date"
/bin/mv ps date
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ ./date"
./date
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ PATH=/tmp:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games"
PATH=/tmp:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo \$PATH"
echo $PATH
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ date"
date
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ rm date"
rm date
echo "minishell\$ "
echo "minishell\$ "

hash -d date

echo "minishell\$ date"
date
echo "minishell\$ "
echo "minishell\$ "