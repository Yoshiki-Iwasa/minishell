PS1='$ '
echo "016_Redirection"
echo ""

echo "minishell\$ echo test > a.txt"
echo test > a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat < a.txt"
cat < a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat a.txt"
cat a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat < a.txt > b.txt"
cat < a.txt > b.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat b.txt"
cat b.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat < a.txt >> b.txt"
cat < a.txt >> b.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat b.txt"
cat b.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat a.txt"
cat a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat < a.txt < b.txt"
cat < a.txt < b.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo 'multi' > a.txt > b.txt"
echo 'multi' > a.txt > b.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat a.txt"
cat a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat b.txt"
cat b.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat < a.txt < b.txt > c.txt > d.txt"
cat < a.txt < b.txt > c.txt > d.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat a.txt"
cat a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat b.txt"
cat b.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat c.txt"
cat c.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat d.txt"
cat d.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat > c.txt > d.txt < a.txt < b.txt"
cat > c.txt > d.txt < a.txt < b.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat a.txt"
cat a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat b.txt"
cat b.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat c.txt"
cat c.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat d.txt"
cat d.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo 'test' > a.txt ; echo 'test' > b.txt"
echo 'test' > a.txt ; echo 'test' > b.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat a.txt"
cat a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat b.txt"
cat b.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo '>>' >> a.txt >> b.txt"
echo '>>' >> a.txt >> b.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat a.txt"
cat a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat b.txt"
cat b.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ rm a.tx"
rm a.tx
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat < a.tx"
cat < a.tx
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ rm a.txt"
rm a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ ls >a.txt"
ls >a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ rm a.txt"
rm a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ ls> a.txt"
ls> a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ rm a.txt"
rm a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ ls>a.txt"
ls>a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ rm a.txt b.txt c.txt d.txt"
rm a.txt b.txt c.txt d.txt
echo "minishell\$ "
echo "minishell\$ "

