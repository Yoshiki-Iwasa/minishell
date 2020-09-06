PS1='$ '
echo "013_RelativePath"
echo ""

echo "minishell$ cd /"
cd /
echo "minishell$ "
echo "minishell$ "

echo "minishell$ bin/ls"
bin/ls
echo "minishell$ "
echo "minishell$ "

echo "minishell$ bin/../sbin/../bin/ls"
bin/../sbin/../bin/ls
echo "minishell$ "
echo "minishell$ "

echo "minishell$ cd"
cd
echo "minishell$ "
echo "minishell$ "
