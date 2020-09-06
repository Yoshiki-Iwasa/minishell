PS1=' $'
echo "004_ReturnValueOfAProcess"
echo ""

echo "minishell$ ls"
ls
echo -e "minishell$ echo \$?\n$?"
echo "minishell$ "
echo "minishell$ "

echo "minishell$ pwd"
pwd
echo -e "minishell$ echo \$?\n$?"
echo "minishell$ "
echo "minishell$ "

echo "minishell$ /bin/ls filethatdoesntexist"
/bin/ls filethatdoesntexist
echo -e "minishell$ echo \$?\n$?"
echo "minishell$ "
echo "minishell$ "

echo "minishell$ cd /zzz"
cd /zzz
echo -e "minishell$ echo \$?\n$?"
echo "minishell$ "
echo "minishell$ "

echo "minishell$ ls | grep zzz"
ls | grep zzz
echo -e "minishell$ echo \$?\n$?"
echo "minishell$ "
echo "minishell$ "

