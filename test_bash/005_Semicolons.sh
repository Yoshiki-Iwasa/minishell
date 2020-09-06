PS1=' $'
echo "005_Semicolons"
echo ""

echo "minishell$ pwd ; ls -a"
pwd ; ls -a
echo "minishell$ "
echo "minishell$ "

echo "minishell$ ls ;"
ls ;
echo "minishell$ "
echo "minishell$ "

echo "minishell$ mkdir tmp ; cd ./tmp ; touch a.txt ; ls a.txt ; rm a.txt ; cd ../ ; rmdir tmp"
mkdir tmp ; cd ./tmp ; touch a.txt ; ls a.txt ; rm a.txt ; cd ../ ; rmdir tmp
echo "minishell$ "
echo "minishell$ "

echo "minishell$ mkdir tmp; cd ./tmp ;touch a.txt;ls a.txt ; rm a.txt; cd ../; rmdir tmp;"
mkdir tmp; cd ./tmp ;touch a.txt;ls a.txt ; rm a.txt; cd ../; rmdir tmp;
echo "minishell$ "
echo "minishell$ "

