#include "minishell.h"

#ifdef LEAKS

__attribute__((destructor))
void  end()
{
  while(1);
}

#endif
/*
 ** コマンドを分割するために  セミコロンの部分をnull にしている
 ** args をあとでまとめてfree するためにNULL で　；　を埋めてる
*/

void	change_semicon_null(char **args, int *semi_co_place)
{

	*semi_co_place = find_semi_co(args);
	free(args[*semi_co_place]);
	args[*semi_co_place] = NULL;
}

/*
 ** シグナルの設定、環境変数をリスト構造に格納、環境変数から$PATH を回収
 ** d_val はシェル変数のリスト
 ** e_val は環境変数のリスト
*/

void	shell_start(char **envp)
{
	t_edlist vals;
	// int i;

	vals.d_val = NULL;
	vals.e_val = NULL;
	setting_signal(); // シグナルハンドルが入っている。この関数以降、Ctrl + C, Ctrl + \ の挙動が変わる。
	if (!update_val(&(vals.d_val), "?=0")) //終了ステータスを表すシェル変数を?=0で初期化
	{
		exit(EXIT_FAILURE);
	}
	if (!init_e_val_list(&(vals.e_val), envp)) //envp に入っている環境変数達をリスト構造にしてリストe_valを作る。
	{
		ft_lstclear(&(vals.d_val), free);
		exit(EXIT_FAILURE);
	}
	commnad_loop(vals); // ここからがメインの処理。この関数以降で入力が行われる。
	ft_lstclear(&(vals.d_val), free);
	ft_lstclear(&(vals.e_val), free);
}

int main(int argc, char **argv, char **envp)
{
	argc = 0;
	argv = 0;
	ft_putstr_fd("                           ■                    ■   ■\n           ■           ■   ■                    ■   ■\n                           ■                    ■   ■\n■■■■  ■■   ■   ■ ■■■   ■   ■ ■■■   ■■■■   ■■■■  ■   ■\n■■  ■■  ■  ■   ■■  ■■  ■   ■■  ■■  ■     ■■  ■  ■   ■\n■   ■   ■  ■   ■    ■  ■   ■    ■  ■     ■   ■■ ■   ■\n■   ■   ■  ■   ■    ■  ■   ■    ■   ■■   ■■■■■■ ■   ■\n■   ■   ■  ■   ■    ■  ■   ■    ■     ■  ■      ■   ■\n■   ■   ■  ■   ■    ■  ■   ■    ■  ■  ■  ■■     ■   ■\n■   ■   ■  ■   ■    ■  ■   ■    ■  ■■■■   ■■■■  ■   ■\n\n\n", 1);

// 	ft_putstr_fd("mgmgmgmgmgmHH9C1>>>;;>>>>>>;>;>;>;>;;;>>>>>>>>?>>>>+?=1>>>>>;;;:::::::;;;>>>>>;::::::::::;:::::::~~~~:~~:;;>;>>>;<<+1zzll=????=??>>>>??====ltttrrtttttttlttttttllllzOvXXXXZtrXWH@ggg@@@g@ggmHHWHHkkkkkkk\n",1);
// ft_putstr_fd("gmgmgmgH90C1?>????>>>>?>>>>>>>>>>>>>>;>>>>>>>>>>;>>;><?=?>>;;;;:::::;;;;;;><~~::;>>>>;;;;;;;::;;;:~~~~~~:;;;;;;;;;:;>?==l=?>>>>>>>>>>>??=lllttttttttttttlllllll==lOzuXOOllltwXH@@@@@@@@@@@qHWWXXzXUWHkkk\n",1);
// ft_putstr_fd("gmgH9VC1=??>>?>>>>>>>>>>>>>;>;;>;>;;>>>;>;;;>;;;;;>>;;;>???>>;;;;;<<~~::;;;>>>>>;>????????<;;;;>;;;;;<_~~~;;;;;;;>>>>==llllzzzlzz1++<;;>?=lllttttttttttllllllll=lltOOz==lllzwWH@@@@@@@g@gHHWUZOtlllllOZW\n",1);
// ft_putstr_fd("W0C<>>>>???????>>>>>>>>>>>;>;;>;;;>;;;;>;>>>>;;>>;;;>>>;;;>??<<<<~~__(;<<<;>++1===lzzzlz=lzzz1+++++<<>><_(+1lzzzzzzzzzlllltrrrrttrttllzz1??=llttttttttttlllll==llttl=????1OXWHHH@@@@@gmmHHXVtlll=llllzOw\n",1);
// ft_putstr_fd(";>>>>>>>>>????????>>>>>>>>>>>;>;>>;>>>>;;>>>>>>>>>>>;;;;;;;;<~~__((;<<~_(++ztttttOwwwwwwwwwXwwwwwwOzl==1?=lllrvwwXuZXXwOtlltrrrtrrrrtltttll===ztttttttttttlllllllll=?>>+zwXH@@@@H@@gmqmqkWkkwOOttttOwXXW\n",1);
// ft_putstr_fd(">>>>>>>>>>>>>???????>>>>>>>;>>;>>;>;;>;>>;>>>>>>>>>>>>>>;;:::((<?<<~~_(+ztl=ltrtvwZyWWWWppVWyZZXUXwOlttllllOwzuZWfWfVVyXwwOrtttrrtttll==1=====llttttttttttllllltOOOzzzwwXH@@@@@H@@@qqmgggmqHWXXzzzvzZyfp\n",1);
// ft_putstr_fd(">>>>>????>???>????=?=???>>>>>>>>>;;>>;;>>>>>>>>>>???>>>;:<::::<<;<_(+ztOz==lltwXXWVfWqHHWWZZZZuvvwXwOttrwwOrzuXWffpppppfffWkXwzzrrttttz=?<<<+1==ltttttttttlltltrwXXXXWHHH@@@@@@HHHHHWHWWUUWWVyuzzzzuZZyy\n",1);
// ft_putstr_fd("??????????????????????=???>>>>;;;>>>>;>>>>>>>>>>>>>>>>;:~~_(;;<++zzOtl=?zztOwXWfWyyfpkqWZuZyyyZyyyyyyXXXXXXWXyyVfpfppffffffVZuuuuuuzzrtO=1+;;;;<<+zrrrttrtttttrruXWWHHHHMHmmg@@HMHUZOOOOltrvuuuvrttOwXuZ\n",1);
// ft_putstr_fd(">>?>>>>>>>>>>>>>>>>>>>??????>>>;>>>>;>;;;>>>>>>>>>>>>;;:(<+>+1zzwuuvrOwwXZZXpWUuXyyyWkqkWXZyyyZuZuzuuZyfpbbpppppppkbpfffppWZyZZuuzzzXuuzOz????>>>>?1ztttrrtrrrrrrwWHMHHHMHWWH@HHMSI=zzzwwXWkkXXOz11zltwX\n",1);
// ft_putstr_fd(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>;;;;;;;;;>;>>>>>>>>>>;::<+zzlzOvvuuuzwwXXVyyyW0ZOXWpWyyppbbpWyyyZyyVWXZXfbbkqkbpffWWfbkbppfVWXWffVyXXOtrwwrtOz+;;<<<;>?=ltrrrrrrrrrwWgHHHMHVwWHHHMHI<zwXWkkHMMH0Oz<<<<1llt\n",1);
// ft_putstr_fd(">>>>>>>>>>>>>>>>>>>>;;;;;;;;;;;:<::;;;;;;;;>>>>>>>;<<+zOvtOwuuXXWWuZXffyXXXXrwwWfffVyyfpkbbpWuzXVpppVVVVVWHHkkWWWZyWWVfpppppbppppffWkwOtrrrvOz+<_::<<<+1OOvvrrrttwWHHMHH0IOXHMHMSI<+zOVUUUUVOI<<~.~(<?=l\n",1);
// ft_putstr_fd("<<<~~~~~~~~~~~~~~~~~~~________`````__~<;;;>>??????==zwvzvvwuZXWWWUuZyXUUzzuwtXWppVWWuZVpbbWWyXvXyfpfVyXUZyyVWWHqHWWXZyyyffVVyfppffVyfWXuzrrrrOv1<<<_::<<+1zOOllltwWHHUC1l=zZWHMH0<~~::<+1===<;<~_._(;??=\n",1);
// ft_putstr_fd("   ``` ` `  `````` `  `               `_~;;>>>>?==lzrzzXuuuuXf0UzuuuuuzvuuuwtXfbpWZZXWWkHWyVWWXzXWppVywrXXuuXXWHkqkHWWffffVVVVVVfffyyVfWXXuuXwOz=??+<<:::;;>>+<<1OWHZ<(+lll=OXHSI<.~~:;;>>>>;:~.._~~<?==\n",1);
// ft_putstr_fd("` ` `   `              ` `            `  _~<>??=lztwwXWWyZuZXXuuuuZuuzzuZyXXrXfpWuXWWkkWVVWppfXXuXfpfyXXrrrrrtwXXWWHkkpfyyyyfppfyXXXwXUWfVyyyXXwwOOz=zzz+<>>>>>>>zOOz=zltlll=zXZ<___::::::;;;;+(+++++>?=\n",1);
// ft_putstr_fd("_______ `           `   `  ` `      `    ` _<??zOwwXWpffyZuuXXZZZyyZXrruZVfWXuXU0wXkkHfVVppppbbWWyVfppbWkXOlOvuZZuuXWWbbWWyyyyWWppWXOtlOwXZuXyyZuzrtlttll1?>>>>??=??=llllttllltv<<_:::~::;;>+zzwwwXWkwzl\n",1);
// ft_putstr_fd(">>>??<_  ` `    `           `  ` `     `` .(+zzwwXZyyZyyZuXXVfyZVVW0rrwXXpppWXrttwXkpfVyVppbqqkbbWkWfppkmHkkkwvuZZZuuuXWWkbbpWXyyyVVZXwO=ltrrrXXuuXwwOrttOzz++>??=l=l==lltttlltz<;;;::::;;>>1wXUXXWWWUZz\n",1);
// ft_putstr_fd("??>>?<_-.   ````````````` `   ` ` ``  ` .(+zOwuZZZZuuZZZZyVVyZZZy0OtrwXXWbffVZwlOXWbpppVVbbpkqqbWMMHkyfWHgggHkkXXyyZyyXXZWWppppfVVyyXuZuXwOtwwwwvXWWVyXXwwwwOOOzz?====lllllttttl?;:;;;;;;;<<<<<1zzz1<<<:\n",1);
// ft_putstr_fd("?=?????<<__-__-_-______-..     `````` ._<ztrzuZyXuuuZyZZZyyZZZyZuwtwwXWbbfyyVXwlwXWbbbfVVWkkkqmHpHMHHWffWHHH@@HHWWVVyVVVVXWpppWVyWWyXXZZyyXwzXZZXuzuXXyVWVVWXXuwO=llll==lllttttz<;;;;:::::~~~::;>>;;;;;;\n",1);
// ft_putstr_fd("====????????????==??++<<<<___ ```  ` _(+zzwwXyyZuuXyyyZyyXWyVffWXvwXWkkbWWZXyXwtwXWWqHVyWqgmqqqHbkHMMHHpfppHHg@HHHHHWWVZXWWWpbkWWWWyyyXuXXyWXuZZuuzzzuuZZyyVfVZuwOttrOllltOOrrtz;::;:::~:~::(++zzwwwwzzz\n",1);
// ft_putstr_fd("=====================????>>:_   `   _+zwwwuZyyyuuyyyZyyVffpfVyXXuXXWkqHWXzuXfWuuXXWbqHyVpkqqkqqmmkqmgmqkkHbppHHMHHHMMHHHkkXuuXWpbbbppWXZZyyyZZZyWWXzvvzuZyZZZyyXXXXwrrrtOwXWWHkkyz(:~~~~:+++zwuZyyVfppWk\n",1);
// ft_putstr_fd("==l=ll=========?=?=======??<_     .(zOvuZZyVVyZZZZZuZVfffpfpfyZXXWpbpVVVyyXWbWyyWkqkbVyVpbkkqqqqmqkkHmmmggmkbbkmHMHHHHHHHMHHkkWVVfpbkbWWVVyZZZyyWfpWXXXXyVfWXuXVVZZZXzvrrXXHHMHMMHko+_::;+OX0Oz1zOOwXXUU\n",1);
// ft_putstr_fd("ll==l=lll==============lll=z<_`` .+zwwZZyyyffWVVyuZXWffffpbbfyVWHmmqkfffffppbWyyWqqkppfppbkkkqkkkkbpkmgg@ggmmmgggg@@HHHHHHHHHMHHHHHqkqqkHkWWWfWZZWbqqWfVfppbWWXVfWWyyuzvrtwXWHMHH#MNky+(+?=?==zzOOwwrrtl\n",1);
// ft_putstr_fd("llll==ll=lll=lllll=ll=l===l=<_  (+wwXWyyyfpbbkbfWuXfppfpWqqbpfWkmgmkppffppbbbpfpWmqkqkbpbkkkkkqqbbbbkqmgg@gqqmg@gg@@@@HHHHHHHHHH@H@HHqmg@gggHbbpbWfpbkHWpppbkkWXWHpWXZuXwOttwWHMM#N##Nkyz???=tvuZZZZuzvr\n",1);
// ft_putstr_fd("lllllll=lllllll=lllllllllllz<_-(zXXWppfVWbbpppHWZyfpfpkqqqkbbWHgggqqkfppppbkkppbqgqkqkkkkqqqqqqqkkkkqqqmmggmqqmg@@@@@@@@HHHHHHHHHHHHMH@@@@@@gmqqkkkkWkqqHHbppkkWWZWbfyZZuzOtOwWWHMM###MHkO==ltrwXuvvrrrr\n",1);
// ft_putstr_fd("llltlllllllllllllllllll==l1<<+jwXVfffVfWkkWWpffyXWppbkqkkkkqqgg@gmqqbVfbkkkqgHbkqgmmqmqqqqmmqqmmmqqqqqqqmgggmqmgg@gg@@@HHHHHHH#HHHHHHHHH@@H@@@@gmmgggqqmmqHpppbbWyyWbWWZuzzwOtwXHH@@HHHMHkz??11zOOlOzzzl\n",1);
// ft_putstr_fd("llllttltttlllllllllllllllllzzOwXVVyyVfWqHWZZffVfpkbbbbbkqqqmggggmqqkpppbbkqmgkbkmg@gggmmmgggggggggmqqqkqmmmggmmgggggg@@@@HHHH#HHHHHHHHHHHHHHHH@@@gg@gggmqqqqkkkbbWWyWkkWWXyZXwtOXWmg@@@HMRI<;;>???======\n",1);
// ft_putstr_fd("ttttttttttttttttttrrrrrrttrwwwXWppVfWWqqbfWWkbpkkpppbkqmmggggggmkkkkkqqqkkqmgqkqg@@@ggggggg@ggg@@@ggmqqqqqqmgggmgmmmg@@@@@HHHHHHHHHHHHHHHH@HHHH@@@@@@@@ggmmmmmqkpfVyppkbpfyyuuzwwXWHgg@HHHkz?11=llzzOtOO\n",1);
// ft_putstr_fd("ttttrrtrrvzzvvvzwwwwwwwwvvwXyWpbbbpWmgqkbbkqkppbpfpkqmggggggggggqbpkqqqqkkkqgmqmg@@@@@@ggg@@ggg@@@@ggmqkqqqmmgmmmmqqqmgggg@@HHHHHHHHHHHHHHH@HH@HH@@@@@@@@@@gggmqkpVyfpbkbpyZZZuXVWVpHg@@@HHkzzOwwwwXXXXX\n",1);
// ft_putstr_fd("vvvvzvrzzzzvrrzXWkWWkWWWXZZVpppbbkqmgmqkkkkkkbbkkqqmggg@gggggggggkpkqqqqkkkqmmmmgg@@@@@@ggg@@@@@@@@ggmqqkqqqmmmmmmqqkqqmmmgg@@@@@HHHHHHHHHHH@HH@H@@@@@H@@H@@@gmmmHWyyWkqkkWyyyZZWWpfpHH@@@HWuZZyyyVVffpp\n",1);
// ft_putstr_fd("vvvvzuuuuuuvOtwWHHH@@@HHWyyfbkbbbqggmqkkkkkbbkkqqqmgg@@@@@@ggg@gqkbkkqqkkbkqggmmggg@@@@@ggg@@@@@@@g@ggqkkkkqqqqqqqqkkkkqqmmg@@@@@@@@HH@HHHHH@H@HHH@@@H@HHHH@@@gggmHWWyWHmmHWVyVyZWpbppHH@@HWWZZZyyVffppp\n",1);
// ft_putstr_fd("uwXuuuuuuZuOllOXH@@@gHHVZyVfpbkkqmgHkqkkbkbpbkmmmqmg@@@@@gggggggqkkkqkkkppkqgmmmmmmgg@@@ggg@@@@@@@@ggmqkkkkkqqqkkqqqkkkqqqmgg@@@@@@@@@H@HHH@@@HH@HH@HH@H@HHH@@gggggqHWVWqmmkWWWWyyWbkkkHH@@HfyZZZZXUUWWf\n",1);
// ft_putstr_fd("<<<<?OXZZZuwz=zXHgggHHWZZyppppbkmqkbbbbkkbbbkqmmgmgg@@@ggg@@@@gqkkkkkkkbppbqmmqqqqmggggggg@@g@@@@@@ggqqkkkqkkbbbkkqqqkqqqqmmggg@@@@@@@@@@HHH@@HH@@HH@@H@@@HHH@@@@@@gmHWbbbqqkqqHWVfpWkkkmH@HHWVVVWXXXuuX\n",1);
// ft_putstr_fd("``   _<<<1zOz?1dH@gHpfyyVpppbpkqqkbbbbkmmmqkqmmgmgg@gggg@@@@@ggqkbppppbbppbkqqqkkkqqgggmggg@@@@@@@ggmqkkkbbbppppbbkkkkqqqmmmmgg@@@@@@@@H@HHHHHHH@H@@HH@@@@@@@@@@@@@@@mqqqqqqkqqkpfffpkqmg@@gmkbpppVyyyXZ\n",1);
// ft_putstr_fd("` ``     .._(;+dHgHpppSZVppfffpkkkbbkqmgggmgggmmgggg@gg@@@@@@gqkkpffpppbppbkkkkkbkkqqqqqqmmg@@@@@gggmqkkbpppppfpppbbkkkkqqqmmmgggggg@@@@@H@HHHH@HHH@HHHH@@@@@@@@@@@@@gqqqmmqkkqqkpVVfpkmg@@@mkbbbbpVyZyy\n",1);
// ft_putstr_fd("((((((+++z++<:<wWbkqHyZZyWfWVfWbbbbWmgggmqqqmmgmg@gggggg@@@@@mqkbpffffpbpppbbbbbbbkkqkqkqqmg@@@@gggmqqqkbppppfffpppbbkkkkqqmmqmmgggg@g@@@@H@@H@H@@H@@@HH@H@@@@@@@@@@@@gqqmmqbbkqkWffVfbqmg@gqbpfppppfVVV\n",1);
// ft_putstr_fd("VVyyVyyVVVWZ<~(zXHgqHyyyZyfWXWffffbqggggmqqqmmgmmgmqmmmmg@@@gmkbpfVVVffpffppbbbpppkkkkkkkkqgg@@gggmqkkbbpfVfffVVVfpppbbbkkqqqqqmgg@gggg@@H@HH@HHH@HHHH@H@@H@H@@@@HHH@@gqqgmqppbkqkkbpppkmg@gmkpfffpppppf\n",1);
// ft_putstr_fd("pppWWbbbbkWk>~(zWHgkWyVVVppbbbbbbWHqqqkqqmgggmqqqqqqqqqqqgg@gqbpfyyyyVfpfffppppffpkkkkbbbkqgggggggmqkbppfyyyyVyyVVVVfpppkkqqqqqqmggg@gg@@@@@H@HH@H@@HHHH@@@HH@@@@HHH@@@gqggHWyVWqqkbppfpWH@gmqkqkbpppppp\n",1);
// ft_putstr_fd("HHHHHHHHMMHRc__jWqmkfyyyfpbbbbbkmgggmmmmggggmqkkqqkpppbkqmggmbpVyZZZyVppfVVVVVVVfpbkpppppkqmggggmmqkbpfVyyZZZyZZyyZyyVVfpkqqkqkqqmggggg@@@@@@@@H@@@@H@HH@@@@HH@@@@@HHH@gmqggHWVWkqbppbpffWgggmmqqkbppppp\n",1);
// ft_putstr_fd("HHHHHH#HH#MHI__jXHmqWyZyfppppbkggggmggg@g@gmqqkqkbpffppbqggmHWyyyZZZyyVyyZZyyyyyVpppfVyfpbkqmggqqkkkbpVZZuzzzzzuuuZZZyZyyfbqqkkkkqmmggggg@@@@H@HHH@H@H@@H@@@@@@@@@@@@@@@gmqkqkppkqkpbbbpbHgggmmqkbbbbbpp\n",1);
// ft_putstr_fd("HHHH##H##HHHI~_+XWqkbfyyVWXWWpqmmmqqqmgggmmqqkkkbpVyVVVpkmmHHVyZZuuuuuuuuuuZZZyyyVfVyyyVfbkqqmqbppbbpfyuuzrrrrrvzuuuuuZZyVpbqkbbbkqmmggggg@@@@@@HHHHH@H@@H@gmg@@@@@H@@@@@@@gqkkkkqqqkkpppbqmmggmqkkqkbpp\n",1);
// ft_putstr_fd("HH#HH#HH##@HI_.(wWkbWWUXuzzXXWqqkbpkqggggqkkbpppVyZZZyyfkqHWVyXXwvvvrrttrrzuZZZyyyZZZZyfpbkqqqbpVfpbpyZZuzrtrrrrrrrrwzuuZyyWkkbppbkqqmmgggggg@@@@@@@H@@H@@@@@gmmmmHMHHHH@gmqbbkkkqmqqbWyVpkqmg@@gqqkbbbb\n",1);
// ft_putstr_fd("H#H#HHHHH#HHI_.(wWqWWzOwwXXWWkkkqmqqkqkqqkkkbpVWXuuzuuyfbHWXUVOtlttllll=ltOwuuZyyyyZyyfpbbkkkbpfyVffWZZuuwttttttll=llOOwwXZWWbbfVffpbkqmgggggg@@@@@HHH@@@@@@@@@gHkkHMHH@H@@gg@@gqqqqqHWZZWkqmggggqkkkkkk\n",1);
// ft_putstr_fd("#HHHHHHHHHHHI_.(dWgHWXuXXppkqkqkqqqqqqqkqkkbfWXXzrrvzuVWUVOOI??===========ltruuuZZZyVfpbbbbppfVyyVyyZuuzOtll==??==????==OOwZWWpVZyyyfpkqqggggggggg@@@@H@@@@@H@@@gmqkqHHH@@@@@@@gggmqqkWyZWqmg@ggmmqqqqqq\n",1);
// ft_putstr_fd("HHHHHHHHHHHNI_`(dWmHVZyyVffppppppbqqqqqqkkpWXXwOttlOwX0VOz??>>>><<;<<?====lttrrrzuyVWbbbbppfffyyyVyZuzvrtllll============lOzuWpVZuuZyyfppkmggggmqmg@@@@HH@@@@@gmmqqkbpbqg@@@@@@@@ggmmqpffWH@@@@mmmqqkkqq\n",1);
// ft_putstr_fd("H#HHHHHHHHHNI_`(wWqpVyyyyyyVfpfVVpqmmmqkbpWXXOOz===llOz1?>;;<<~~~::;>?=lltttttrzXXWpbbpffVyVfVyyyyXuvrtttlltttrrtttlltltllwzuXfVyZZZZZyyfpkqqqmmmmmgg@@H@@@@@@@ggggmqkkqmg@@@H@@gmggmqbbkH@@@@gmmqqkkkqg\n",1);
// ft_putstr_fd("HHHHHHHHH@HNI_`(zWkfyyVyZZyfppfyVWH@gmqbfyXzrtl=??==???>;;;::____(+zzzlzOrrrrvuZyVffWWXZZZZyfVyXXuzrttttttttrrvvuuwwwwwXXwXXXWpppWffVyyyVfppbkqqqqqkqg@@@HHHH@@H@@ggqkkppkmg@@@@@@gmqbbkqg@@@@@gqkqkqmg@\n",1);
// ft_putstr_fd("HHHHHH@@@@HNI~`(zXkpfVVyyyffffVypqg@@mkbfZXrtl=????>>;;;+++1zzzzzOwwXXXXXXuuuuzzzuuXzzzzzuuZZXXwrrttttttttrzuXXXXWWWWWWWWWWWHkqqkqqkkWpppbppppbkkkkbkkqm@@@@@@@@@@@@gqkbpbkm@@@@@@gmkppkqg@@@@@gmqkqm@@@\n",1);
// ft_putstr_fd("HHHH@@@@@@@MI_`(zXmkpVWyVffpffffWq@@@mkpVXwtl=??>;;;++zzOwwwXXXXXWWWWWWHWWWWXXXXXwzzzzvvzzzzzvrttttttttrrwXXXWWWHqqmHHHHHgH@@@@@@@g@ggggmqqkbppppbpppbbkqmg@@@@@@g@gggqkbpbHHHHH@@ggkbbkqg@@@ggmqqqg@@H@\n",1);
// ft_putstr_fd("H@@H@HHH@@HMI_._zXgqpyZXfpffppppkH@@ggqpWXOl==??>++zzwXXXWWpkkqqqggH@@@@@@HHHHkWWWXXZZuuzuzvrrrttrrrrvvzuXXWWqmg@@@@@HH@HHHHHHH@H@@H@@@@@ggmqkpffffffffppkqg@HH@@@@@@ggqkkbpH@@@@ggmqkkqqmggmqqqkqmg@@H@\n",1);
// ft_putstr_fd("H@H@@@H@@@@MI<`_jXgHpVfppppppppbqg@@@gqWXOl==???zzwXXWpppkkqgg@@@@@H@@@@@@@@@gqqkbbpVyyZZuuzvvrvvzzuuuuuZVpkqgg@@@@HHHHHH@@@@H@H@H@@@@@@@ggggqkpfVyyZZZyWWWHg@H@@@@@@@@mqqqHH@H@@gmmqqkkqqqqqqqqqqg@@@@@\n",1);
// ft_putstr_fd("HH@HH@@@@@HM0<`-jXgkffWkkbppppppkmg@@gHWXtl???zzwXXfpbbbkkqqmmmggggHHgHmmgg@@gmqkkkpffVVyZuzvvvvzuuuuZZyVpbkqmg@@@@@@@MHHHHHHHHHHHHHHHHHHkkkkkkpfyyZuuuzuXWWHH@HH@H@HH@@gmH@HHHH@@mmqqkqqkqqqqqqqqg@@@@@\n",1);
// ft_putstr_fd("HHHHHWUUUUU0>_`-+XmkbpkkkkkbpppbqqqmggHWXl====truZWfVVVVWyWWfWWppppfppppppbHHHkkkkbpffffVyZuzvvzuuZZyyVfpbkqqqmmmmmqqkkkbpppfffffffppfffffffVyyXXuuzzvvvvzuWWHMHHH@HHH@@@@@@HHHH@@mmqkkqqqqqqqqqqm@@H@@@\n",1);
// ft_putstr_fd("zzzz1++<<<+-_ `-<XqkkbkqqmqpffbqmgmmgqWXZl===lltrvXXuZuuuZZZZyyyyyyyVVVVyyyyyVVfppfppppffVyuuzzuuZZyyfppbkkkkkkkbbbbppfffVyyyyyyyyyyVVyVVVfVyyXXXwwOttttrwwXWWH@@H@@HH@@@@@H@@H@@gqqqqqqqqqqqmmqmg@@H@@@\n",1);
// ft_putstr_fd("kkkkkkkkkkWkI<  (XqqbbkkqqqkkkbbqgmgmkW0Ol====lltwwwXuuuuuZuZZZZZXWVWffpffffyyyZyyyVVVffVVyZuzzzuuZyVfppbkkkkbbbbppppfpppppffppfffffVVVWWWWppbbbbppkkAAwwOwwXWHH@HH@HHH@HHH@@@@@@gmqqkqqmmmmmqqqm@@@HH@H\n",1);
// ft_putstr_fd("HH@@H@@@@@HMk<- (dmqqkqqqmmqqkbpHmgmqHWXrOzzzzOwwXZyyZZZZuuuzzzuWfpbbbbbbbkbppWWWXyyVVyyyyZuzzvzzuZyyfpbbkkkkHWWWWWyyyyVfppffffpfVyyyyZZZZZZyyyXUUUWHMMHHkkkXXpHg@H@H@H@@H@@@@gggmqqqqqmmgmmqqqqg@@HHHH@\n",1);
// ft_putstr_fd("@@H@@@@@@@@Mk>_ (dqqqqqqqqqqqkpppHmmHWZXXWWWW0ZOOwwXXXZZXuzvrrvuZVppbbbbbbpppppppppppWWWVyXXuzrvwXXWWWkkkbWWWyXXOwwXVWWWWWWHHHHHHWWbbbWWWWyyZyZXwwOtZWMHHH@HWWWH@@@H@H@@@@@H@@gmgggmqqmggmmmqqmm@@HHHHHH\n",1);
// ft_putstr_fd("@H@@H@H@@@@Hk>_ (dkkkkkqkkkqkppffpqkppWWbHUUOI=ltrwvzzuzzzwXXXXXWWHHHHHHHHHbppVyZXXUWWqqqHHHkXXXWHHHHmqkWVyyZZuvtOwXWqqqmg@@gggg@gmqkqmmmqHWfyyZuuuOOXWMHHH@mqqg@@@@H@@@@ggHgggmmgggggggqqqmmmgg@HHHHHHH\n",1);
// ft_putstr_fd("H@@H@@@@@@@Mk>_ (dqqqqqqqqqkkpppfVppbHmmHXXOllltrrrvvzuuXXWWpWXXWHggg@@H@@gqbpfyyZuuXWWqmmHHHWZWWHMM@gqbVyyyyyZuzwXWqHHWWH@@mgg@@HHWWkkqmmmqkpVZuuzrrwWMMHHWUUWWHHggHmggmqbWUUUUWHggggmmmqqmmmg@@HH###HH\n",1);
// ft_putstr_fd("@H@@@@H@@@@HRz_ (dkmmqqqqqqqHHHbpVVpHggmWVZXOtrttrrzuXXWbkkbWXwwXWHgg@@@@HHbbkbfyZuvvXWHHH0Zvzz111zwWHbpyZyZyyyZyWWkbfyZWWHggmgmHHWyyVfWWWWWWWWZuvrtrwXHW0OOOOwXWppHpWbkkkW0I<><+XHmmqqmqqqmmmg@@H#NN##H\n",1);
// ft_putstr_fd("@@HH@@@@@@@HkI_ (dkqqqqqqqHU0CO0UUWyWHHgHWXXtlttttruZyyfpWWWyyXwwXWHHg@ggqppbkbpyZuuzXWWHSZz???>>?==wXWHWZZZZZZZyVpbbppppppbkHppfVyyyyZuXwOOOOOOrttlOwXW0ll==ltwXyyyyyyyWUUVOlzzzwXWqqqqqqqqmg@@HH#####H\n",1);
// ft_putstr_fd("@@H@H@@@@@@HkI_`(dWmmqqmmHSI::<1zOwzzZXHW0OOllllltrwwXX00XXzXuZZZZyfpkkkkbbbbbbpyZuZXWWbWXOz===llzzOwwWbfffWZuuZZyVfffppffffVyyyyyyZZuuzrtl===lllll=zwX0Z====lltwXuZyZuuzvOOOwwXuuXWqqqmmggggg@@HH######\n",1);
// ft_putstr_fd("@H@@@HH@@@@HHI_`_dWmmqqmgH0z<<;>1ltrOzzXyXI?===llllllll=llltrrzuuZyyVffpppppfffVyZZXpbkpWXrll=1++1zwuXWffppWkXuuZZZyyyyyyyyyyyyyZZZZuuzrrtll==l===??zwXZv?==l=lltOwuuuzzzuuuXXfWuuXkqqqqmgggg@@@H#NNNNN#\n",1);
// ft_putstr_fd("@@@@@@@@@@HMHI_`-dWmmqqmgH0Ilzz?>1ltlz1OXXI?==?===l====?===lttrvzuuZZyyyyVyVyWXXuXXWkkbfWXIz<<<<_~<zwyfppbkqH0vvwXzuuZZZZZuuuuuuZuuuzvrtlll====?????zwVI===l=====lOOrzuZuuuXXpfWuuXHmqqqmmggg@@HH#NNNMN#\n",1);
// ft_putstr_fd("@@H@@@@@@@HMHI_`(dWmmqqqmHXO=tz???llz<;<zuO=?========?=======lttrrvzuuuuZuXXZwOrrzXWWbWXXOz<~~~..._<zwXfppWW0wttlttttOwrvvvvrvvvrrrttlll==?????????1zuZ==========lllruZZZzrwXVVZuZWqmqmmmggg@@@H#NNMNNN#\n",1);
// ft_putstr_fd("@H@H@HH@MHHHHI_`.zWmmqqqmH0I=lz=====?;;;zXvO=?=l===?????????===llttrrrrOOOttlllltrrwWbW0Oz<~~~~....:<1wXpWWXrtttllll==llllllltttttlll===????>>>??>+zuwI??=====???==lruZZuzrtwXVSuXWqggggggg@@@HHNNMMNNNH\n",1);
// ft_putstr_fd("@@H@H@@HHpffVk+-.zWmmqqmmHXOlrrtz?>>>;:;+zOOz??======???>?>???===lllllll=======lllOwWHWZz>::~~~~.._::>1OWHkkwtttl========???==l====????>??>>?????1zwXO======??????=lrXyyZXXwrwXZuXkmmggggg@@@@HHNMNMNN#H\n",1);
// ft_putstr_fd("H@@@@@HHpppppfWw+dWqmqqqqHkZlrrO<;>>>;;;;<zOOz>=====????>>>>>>????=???=========llzwXWUOz>;:::~:~...~:;>1zXWWXwrtll===?==?????????>>>>>>>>>>?>>?1zwuZOl=l=????????==zwXWpffWXwtwXXWqggggg@@@@@@HHNMMNN#HH\n",1);
// ft_putstr_fd("H@H@@HkbbbbbpppffWWqmqqqqHHklrtz<;+>>>>>;;<1OO+<+?=?????>>>>???????===========??zwu0Oz?>;::~:~~~~..~:;;>>1OwuuXwOll=??????>>>>?>?>>;>>>>>>???1zwzwZOlll==?==??=?===zwWkkbpfyXrtwXWmgggg@@@@@@HH#NNMNNHH@\n",1);
// ft_putstr_fd("HHHH@qbbpbbbbppppbkmmmqqqgHkXOz=??=????>;>;<+ztzz====????????==============???zzwXZtlz>;:::~~~~~~..~::;;>>+zOvwwwwwOl==lzzzzzzz1??>>>>1zzwwwOtOOOllttlll===========zOXWpppVXZttwWmggg@@@@@@@@HH#NNMN#H@@\n",1);
// ft_putstr_fd("VUWHHHpbkqqqqqkbbkkqqmmqHWUykO=??===???>>;;;>+1zOtrrOl=========l=llllllllzOwwwrOOtlz<>>;:::~~~~~...~~::;>>>?zrrrrwrrtrvzwXXZXXXXwwOO===lOOOOz===llttltll==l======l=ltwfpVWXXOlwXHgg@@@@@@@@@@HH#NMN#HHH@\n",1);
// ft_putstr_fd("  `~?OWqmmmmmqkkqqqqmmqkbWWHHkz>?lll?=?>>>>>>>???=zlllttrrrtttrrrvzuuuvrrrrrwOtlltl=?>>;;::~~...~..~~~:;>>>?ztwuXwOttttttOOOOOOzz1=?==?======lllltttttlllllllllllllltwyWXXwO1zwWg@@@@@g@@@@@HHHNNNN#HHHH\n",1);
// ft_putstr_fd("```` _?WHqmmmqqqqHHHHmmgg@H@MHI>?=tO=??????????=====lllllttttttttttllltttttllllttttl?>;;::::~~.~~..~~::;>>??zOXZyZyZuzvvrrrttttlllll======llllllllttrtllllllltltttrrwwZuXOO=?zXH@@@@gg@@@@@HHH#NMMNHH@@@\n",1);
// ft_putstr_fd("....`` ?UHmqmmmHH00VUUWHHMM@@Hkz?zrt=??????????==?====lllllllllllllltlttltttrrrrrrl=?>;:::::~~~~~~~~~:;;;>??==zXXyyyZuuuzvvrrrtttllllll=lllltrttllttttlttttttttttrrzzuXXOl==1wWg@@@@@@@@@@HHH#NMMMNHH@@@\n",1);
// ft_putstr_fd("~....`._(UHgqkHWSwOzzltrwXWHHMHwz1Ot=??????==????======lllllllttttttlttttrrrrrvvOOz<>;;;;::::(:;;<(::;;;>??????+zXXyyZZuuzzzzvrrtttttttlllttttrrttltttttrrrrrrrrvvzzOOzzlzzzOXWg@@@@@@@@HHHHH#NMMNMH@@@g\n",1);
// ft_putstr_fd("+(-_____(zUHkpfyZXzzwwwXvrwWHMHkI>1===??=??=======?======llllltlttttttrrrvvvvzvOz<<<;;;>>;;;+>>>>>???>????===?>>>1OXVVyZZuuzzvrrrrrrrrrrtttrrttttttttttrrvvvzvvzzzzwO=>?zrttwXHmgg@g@@@@@@H@H#NMN#H@@ggm\n",1);
// ft_putstr_fd("QQQQQQQQQQkHHffffVyZZZZZXZOXWmHHI+>>???=?????==?======l=llllltltttttrrrvzzzzvzZz>::+<>?????=======lll==zzzlltzzzzzzwVpfyZuuuzvvvrrvvvvzvvvvrrrrtttrtrrrvzzzzzuzzuzwO=???1zlOXWqggg@@@@@@@@@HH#NN#H@@@ggm\n",1);
// ft_putstr_fd("WHMHH##HHHHMSZz1zOXXVVVW0I<dWHHNkO<>???===??=?==?======llllltlltttrrvvzzzzzzzrO?>+1111==llllltttttrrwwwzuwwwkkXwwwwXfffyZuuuzzzvvvvvvzzzzzvvrrrrrrrrrvvzzuuuuuuzuzrl==?>;>1wWqmggg@@@@@@H@HHH###HH@@gggm\n",1);
// ft_putstr_fd("XWHMH##HH@@MS<`   _?zCz<<<zXH@HMHkz?>????================llllttttrrvzuuuzzzzzvOzzzOwwwwwwOttrrrvvzzuuZZZXWWHHHHWZyZyyZZuuuuuuzzzzzvvzzzzzzvvvrrrtrrrrvzuuuuuuuuuuvtl===?>+zXWggggg@@@HHHHHHH#NNHH@@ggggm\n",1);
// ft_putstr_fd("WVWHMH#HH@MMS< ` ```.` _+1zWH@HHHHkz~<>?????==?========ll=llttttrrvzzuzuzzzvvvrrrvwXWH@@HkkwvvvzuuuZZyXWW@@MMqbpfVWXXXvvvvzzzzzzzzzzzuzzzzzzvvvrrrrrvzzuuuuuuuuuzrl=????1zdWggg@@gg@@@@HHHH#NN#H@@@ggggg\n",1);
// ft_putstr_fd("WZWWHMHHHH#Mk>_``` _((+zwOOW@@@HHMkI_:>>??=??==?=====ll=llllltttrrvzzzzzvrrrrrrrvuuyWWHHHHWZuuuuZZZyyfbkqqHkkbbbWWXOllllttrrrzzuuzzuzzuzzzzzzzzzzzvvzzuuuuuZZuuuvtl==zzzwXWgg@@g@@@@@@@@HHHNNN#H@@@ggggg\n",1);
// ft_putstr_fd("ZuuXWHMMMMMMRc_ `._+uwXWWkzWH@HHHMHk<:;????=?========l=llllltttrvvzzzzrrttllllltwwuuZZuuuuuuuuZZZyyVfppppfVVffWW0ZOlll==lllltrwvzuuuzuzuzuuuuuuuuuzzzzuuuuuuZuuvrrOwwwwXWHgg@@@@@@@@@@@HH#NNMN#H@@@@@@@@\n",1);
// ft_putstr_fd("yyZZuWHHg@MMHI_``.(OXWmqH0zWMH##HHMHw+;>?????=?==?===lllllltrrrrvzzzvrtlll====lllOwzuuuuuuuuuZZZyyyyyZyZZZuXX0XZOl=ll=l==llllttrrzuuuuuzuuuuuuuuuuuuuuzuuuuuuuuvwXXWWWWqggg@@@@@@@@@HHHHHNNMMN#HHH@@@@@@\n",1);
// ft_putstr_fd("HHHHkWfbqmMMHI_``.(wWkqkHIzW###N#HHHkOz>????===??======llltttrvvvvrrtl=========lllttrrrrvvzzuuZZZZZuuzzuuzvrttll=======lllllltttrrvzuuuuuuzzuuuuuuuuuuuuuuuZuuzvXWHgggggggg@@@g@@@@@@HHH#NMMN#HH@@@@@@@@\n",1);
// ft_putstr_fd("Mqg@@HbkkgMHHI_`..(zXffVWZzW###NNNHMHWwz=???====?==?===lltttrrrvrrtl====??===llllllltttttrrrvzuZZZZuzzvvrrrrtlll=======lllttttttrrrvuuuZuuuuuuuuuuuZuuuuuuuuuuvvXWH@@@@gg@@@@@@@@HH@HHHH#NMNN#H@@@@@@ggg\n",1);
// ft_putstr_fd("gqqqmqkqqgHHH0_``.(zXyyZXIzWHH#NNNNMHWXwz??=??=?==?====llttrrrrrtll========lllllllllllltttttrrzuZZZuuzvrvrrttttlllllllllltrrrrrrrrvvzuZZZZuuuuzzuuuuZuuuuuuuuzvzXHg@@@@@@g@@@@@@H@HHHHHH#NNN#H@@@@@@@@@@\n",1);
// ft_putstr_fd("ggmmqkkkqg@HH0<...(zXyZuwz1XH###N##MHWyXO??????=??====lllttrrrrtll======llllllllllllllllttttrvuuZZZuuuvrrrrrrrrrrrtttttrrrvzzzzzzzvvzzuuZZuuuuzuuuuuuuuuuuuuzvzXWHgg@@@@@@@@@@HHHHHHHHH#NN#HH@@@HH@HHHHH\n",1);
// ft_putstr_fd("qqqmqqkkqg@HHk<...(zuyZZXz1XH###NN#MHWyVkz?>??=?=?=====llltrrttll==l==llllllllllllttttttltttrvuZZZuuuuvrtrrvvvvzzzzzzzzzzzuuuuuuuuuuuzzuuuZuuuuuuuuuuuuuuuuzzzuXWgggg@@HHHH@HHHHHHHHHHHNNN#HHH@HH@HH@@@@\n",1);
// ft_putstr_fd("qmmmqkqkqgMHMR<...(zZyyZXz+X##NNNN#@HWVpkOz>????==??==l=llttttll==llllllltlltttttttttttttttttrzzuuuuuzvrrrvvzzzuuuuuuuZZZZZZyyZZZZZuuuuzuuuuuuuuuuuZuuuuuuuuzzXWH@@g@@@@@HHHHHHHHHHHHHNNNN#HHHHHH@@@@@gg\n",1);
// ft_putstr_fd("WHHgggmmmmH@MR>...(zZyyZXz+X######H@HWVpWkz>>??????=====lllttll=lllllltttttttrrtrtttttrtttrrvzzvvrvvvzzzuuuuZuuuuZZZyyyyyyVVVVyyyyZZZuuzzuuuuuuuuuZZuuuZZuuuuuXWg@@@@@@@@HHHHHHHHHHH#NNMMNHHHHHHHHHHHH@@\n",1);
// ft_putstr_fd("fVfWHmmqkkHHW0<~..(wXVyyXv+XH###HHH@gHfpkkI>>????????===lllllllllltttrrrrrrtrtrrrtrrrrvzzzwuZZZXXwwuXXXXWffppfpffppppppWWWkkkpffyyyyZuuzvzzuuuuuuZZZZuuZuZuuuuXH@@@@@@H@@H@HHHHHHH###NNN#HH@@@gHHHHHMMHH\n",1);
// ft_putstr_fd("bpfffpWkkbppWk>_..(wypVyXv+XH###HH@@HHVfHHkz?>>??????====llll=lllltrrvvzzzvrrrwwvwuuuuZZyyyyyVVfVyyVfpbbbkkkbkkqqqqqqqmgmmmqkbpVyyyyZuuzvvvvzuuuZZZZuuuuZuuuuZWH@gg@@@@@H@H@HHHH####NNNN#H@@ggmqkbbbbbkk\n",1);
// ft_putstr_fd("kkbppffppbkHHHI_..(wWppyXI+XMNNN#H@@@HWWHHkwz>?????=?========l=lltrvzuXXXXXkXXXXyyyyyVVVVVfffffpppppbkkqqqqqqqqqHHHHHHHHHHWpWVyZZyZyZuuzvvvzzuuuZZZuuuuZuuuuuXWg@g@@@HH@@HHHHHH#N##NNNMNNHH@@@@mqkbbpppp\n",1);
// ft_putstr_fd("qqkkbbppppHHHNI<..(wWbpVXI+X#NNN#HH@H@MMH@Hkz?????????=======lllltrzuZyVfppppppppfppppbbbbbkkbkkkkqqqqqqHHHHWUUUU0XXZyyyyZyZZZZuuZZZZuuuzzzuuuZZZuuuuuZuZuuuXWH@@@@@H@@H@@HHHH#NNNNNNMNNN###HHH@gqqkkkbp\n",1);
// ft_putstr_fd("mqkkkkkbppbHMNI<..(wWkpVXI+X#NNN#HHH@HHHHHMHwz>?>??????=========ltrvzuuZZuXXXXWXXZXXUUUUUUUWWWWWWHHHWWUU0ZOvzzlltrvuuuuuuuuuuuzuuzuuuuuuuuuuZZZZZZZZuuuuuuZyWH@@@@H@@@H@HHHHH##NMMMMMNMMMNN#HH@@gmmmmqkk\n",1);
// ft_putstr_fd("gmqqqkkkbpbkmHI<..(wWbpVXI+X#NNNN#HH@HHHHHHMkO>??>??????=======llltrrvvrrvrrrwrwvvzzzzvrrtrwwXXXXXXZOOtttlllllOrrvzuuuzzzvrrrrvzuuuuZZuuuZZZZZZZZZZuuuZZZZyWHH@@@@@H@HHHHHHHH##NNMMMNMMMMMMMHggggggggggg\n",1);
// ft_putstr_fd("@gmqkqkkkbpbmHI<` (wXkbfSI+XM#NN##HHH@HHHHHHMROz>?????=?===lll==llttttttttttttttttrvvvrrtttttttlttlllllllttttrvzzuuuuuuuzvrrrvvzuuZZZZZZZZZZyZZZZZZZZZuZZVWWH@@@@@@HHHHHH#####NNNMNMMNMMMM@ggggg@ggggggg\n",1);
// ft_putstr_fd("@@gqqqqqkkbbmHI<` (wWkkpSI+XMHHH##H#HHHHHH#NNNkI>?????==?====ll=llttttttllllllllltttrrrttttttlllllltttrOrrwwuuuZZZZZuuuzvrrvzzuuuZZZZyyyyyyyyyZZZZZZZZZyyWHHH@@@H@H@HHHHH####NNMMMMMNNMM@gg@@@@@@g@ggggg\n",1);
// ft_putstr_fd("@@@gqqqqqkkWHHk<  (wWkkpWI+XHHHHH####HHHHH###HMkOz??==??=======llllttttttllllltlltttttttttrrrrrvvvwwuuuuuZZyyZyyyyyZZuuzvvzzuuuuZZZyyyyyyyyyyZZZZZZZZZyWWH@@@H@H@HHHHHHH#N###NNMMMNN#H@@@g@@@@@@@@@@@@@@\n",1);
// ft_putstr_fd("@@@gggqqqqHHMMR> `(zWkkpWI+XHHHHHH####H@@HHHHHHHHwz?====?===l=llllltttttttlllllltltttrrrvzzzuuuuZZZyyyyyyyyyyyyyyyZZuuzzvzzuuuuuuZZyyZyyyyZyZZyyyZyyyyWWggg@@@HHHHHHHHHH#N###NMMMNNHH@@HH@@@@gg@@@@@@@@@\n",1);
// ft_putstr_fd("ggg@gggmqmHM#MHI   +XqqbWI+XMHHH######H@@@HHHH@HMHkzz====?===ll=lllltttttlttltltttttrrrrzzuuuZZZZyyyyyVVyyyyyyZyZZuuzvvvvzzzzuuuZZZZZyZZyZZZZyyyyyyXVOXWHgg@@@H@HHHHHHHNN###NMMMMNHH@@HHHHHHH@@@@@@@@@@@\n",1);
// ft_putstr_fd("mmgg@@ggmmHMHMHI   _zWmqWI+XM########HHH@HHHHHH@@@HkkOz?====lll=lllllttttllltltlltttttrrvzuuuZZZyZZyyyyyZZZZZZuuuzvvrrrrzzzuzuuuuuZZZZyyyyyyZyyyyWXZtzz1ZWH@@@@HHH#HHH#NN##NNMMNMMH@ggHHHHHM@@HHHHH@@@@@\n",1);
// ft_putstr_fd("ggqqmg@gmqqHMMHI `  (XHHkI+XM#N#####N#HHHHHHHH@HH@@HMHkO=llllllllllllllttllttltltltttttrrvvuuuZZZuuuuuuuuuuuuzzvrrttttrrvzvvvvvzzuuZZZyyyyyyyyyyZXwttwOzzOWH@@@HHH#N##NNNNNMNMMMHHHkkkkkkqqmgggHHMHHH#HH\n",1);
// ft_putstr_fd("gmmmmgg@gmqkHgHI_` `-?UHHI1XMNN######N##H#HHH@@@@@HHMMH0?zzzllllllllllltllllltltltltttttrrrvvzzzuuuuuuuzuzvrrrttttttttttrrrrrrvzuuuZZyyyyyyVVyyZuzrlzwXO<<zWMMMMHHH#NNMMNNNMMHkbbkbpppbbkkkqqqqmmg@@HH##\n",1);
// ft_putstr_fd("gggmqqqg@gqbbkHI_``   ?TC<(dMNN#####NNN###HHHHHHHMHMH0<+1wXkwwOOlltlllllllllllllllllllltlttttrrrrvzzzzzzrrrttttttttttttttrrrrrvzuZZyyyyyVVVVyZuuzrt=zXWXz___<?OVHMMMNNNNNMMMgqkkkbppbbbbpppbkqqmggg@@MMH\n",1);
// ft_putstr_fd("@ggmqkkqqmmmkpWI_` __``.__(dMNNN####NNN##HHH@H@@MM961++wXWbkHkkkXOttttlllltlllllllllllllllllttttrrrvvvrrrrttttttrttrrrrrrrvvvzuuZyyyyVfffVVyZZuuzrt=zXWkkz<~~___<?7WMMMNNH@@@ggqkkbbbbbbkkkkkqqqqqqqmggg\n",1);
// ft_putstr_fd("@@ggmqkbbkqmqkkI_` `_`` ~_(dMMNNN####NN###HHH@HHUC1+zwXWpkkqmggHHkttttrttlllllllllllllltttttttttttttrtrrrrrrvvrvrvvvzzzzzzzuuuZZyyyVfffffVyyZuuuvrtlwWgHkOz<~~~~~__(?WMMMMHgg@gmmqkbbpkkqqmggmmggmgmqmmm\n",1);
// ft_putstr_fd("@@@gggqHkbkkkkHI<-````````(dMNNMNNNNN##NN#HH@MHC<+jwXVVpkkqqgg@@HkwlltrrttttltllltltttttrrrrrrrrrrrrrvzzzzzzuuuuuuuuZZZuuuZZZZyyVVffpffffyyZZuuuvrrtwWHMHkO<_~~~~~:~~~?vWHqkkkkkqqmqqkkkqmg@@@@@@@@@@@@@\n",1);
// ft_putstr_fd("@@@@@@g@HqqkppfI<_ `````  (dMNMNNNNN###NN#HMHSz<+wXyVppbkkqgg@HH@HkOlttrvvrtttttttttrrrrrrvzzzuuuuuuuuuZZZZZZZZZZyyZyyyyyyyyyyffppppppfVyyyZuuuzrrrvXWHHHSwz<_~;;::~~___?XWkkbbbkkkqqmmmggg@@HHHH@@HHHHH\n",1);
// ft_putstr_fd("@g@@@@@@@@@gHHHk<_ ``.``_.(dMNNNMNNNN##NNMMM0<<+OXyyVppkkqmg@@@HHHkZllltrvrrrrtrttrrrrvvvvzuuuuZZZZZZyZyZZZyyyyVyyyVyyyVyVVVfpppfffpfVyyyZZZuuuzzvvzXWHHHWXO+<:::::::::~~<OWWppbkqqmg@@@@@@@@@HHHHHHHHH#\n",1);
// ft_putstr_fd("@@ggg@MMMMMMMMMHz_` `.` ~.(dMMMMNMNNMMMMMH0z>+wXZZyVfpbkqqmHHHMHgHkktlllttrvzzzzvrrrvvvvzzzuuZZZuZZZyZyZyyZyyyyVVyyVVVVVffpppfpfffVVyyyZZZZZuuuzzzzuWWHHHWXwI<:::>>++(__._<OXyyWWHHg@@HHHHHH@@HHHNN###NN\n",1);
// ft_putstr_fd("@@gg@H#NMNN#MMMHI_.  `` ._(dMNMNMMMMHHU0Oz<(1wuyyyyfppbkqg@@MHmHMHHkOllllttrrvzzzuzzzuzuuuuuuZZZZZZZZZZZyZyyyyyyyVVyVVffppffffVVyyyyZZZZZuuuuuuzzuuuXWHHHfyXOzz<:~<+z1<<__(+wfVyZyWHHHM@HHHH#HHHHHH#N##N\n",1);
// ft_putstr_fd("@@gggM#MMMNHH@@HI<__ ` . `.dMMMMHWUXvrrv<~<zXZZyyyyVfpkqqggHHHMMHMMWwllllltttrrrvvzzzzzuuuuZZZZZZZZZZyyZyyZyyyVVyyVVVfffffVyyyyyZZyZZZZZZZZZuuuuuuZZWWH@HfZuzrO+<~(++<::<<:<dWppfWyyyWWHHMMH##HHHHHHH###\n",1);
// ft_putstr_fd("@@ggg@#NMM#H@@@HI~``` __.`-zWWUXuuzzzvI<++zwZZyyyyVfpbbkqgmkkHMMMHHWXrlllllltttrrrrrrrrrrrvvzzzzuuuuZZZZZZyyyyyyVyVVVVVVVyyyyZZZZZZZZZZZuZuZuuuuuuZyWHggHfVyXXwOz<:<+?1++_~(zXWkbppfWWyyZXWHHMM##N#NNNMN\n",1);
// ft_putstr_fd("H@@gg@MMNN#H@ggKI_  `.~~___juZuuuzuuwI<:+wXyZZyyyyyVfpbkqqkpbqg@qkbVXttllttttttttrrrrrttttttttrrrrvzuuuuuZZZZZZyyyyyyyyyyyyZZZZZZZZZZZZZZZZuuuuuuZZVpqgHW0z1zOXwI<<~:;><<?<(+wWqkbbbppfVyyyyyWWHHMMMM##N\n",1);
// ft_putstr_fd("@@@gg@H#NNN#M@gWI_`  .~~:~_juZuuzuZXO<<+wwZyyyZyyVVVfppkkkbfWHgmkbpfXOlltlllttttttttttrtttrttttttrrrvvzuuuuZZZZZZZyZyyyyyyZyZZZZuZuZZZZZZZZuZuuuZZyfWmH0>_   _~<<::(<1=<<:<>?zWkkkkkkbbpfffVVVyyZXWWHMMH\n",1);
 	shell_start(envp);
/*
 ** ここ以降の条件分岐は、argc と argv がunused で起こられないため。
*/
	if (argc == 0 && argv == 0)
		return EXIT_SUCCESS;
	if (argc != 0 && argv != 0)
		return (100);
}
