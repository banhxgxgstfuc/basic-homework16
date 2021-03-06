#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 50    // 最多輸入位數
#define MAX_SPECIAL_UNITS 5    // 特殊單位個數

int main() {
	char su[MAX_SPECIAL_UNITS][3] = { "萬", "億", "兆", "京", "垓" }; // 特殊單位
	/* 萬、億、兆、京、垓、秭、穰、溝、澗、正、載、極 */

	char input[MAX_INPUT + 1];
	char output[MAX_INPUT * 4 + 1];
	char output_tmp[MAX_INPUT * 4 + 1];
	output[0] = '\0';
	char tmp_ch[5];

	printf("input: ");
	scanf("%s", input);
	/* 先把讀到的字串存到 input 這個陣列裡面，至於input要多長，根據希望的位數調整MAX_INPUT
	 * 這個數字大小會影響到output陣列的大小，例如輸入10位數字，最多可能要輸出20個中文字
	 * 一個中文要兩個char來存，所以至少要10*4個char，多加一個char是為了放'\0'表示結尾　*/

	int i, cnt_su, cnt_nu;
	/* cnt_su紀錄現在要輸出 "拾", "佰", "仟"
	 * cnt_nu紀錄現在要輸出 "萬", "億", "兆", "京", "垓" */

	for (i = (strlen(input) - 1), cnt_su = 0, cnt_nu = 0; i >= 0; i--) {
	/* 如同我們平常數位數的方法從個位數開始數 ，所以i從(strlen(input) - 1)字串尾端開始往前數
	 * strlen(input) 是用來計算input字串的長度，例如輸入abc則strlen(input)=3 */

		tmp_ch [0] = '\0';
		output_tmp[0] = '\0';
		/* tmp_ch 是用來暫存目前數到的數字對應的輸出，至於如何對應看一下範例
		 * 例如、我們輸入123，則拆成 "壹佰", "貳拾", "參" 三組內容，程式是從後面開始看，所以他看到的字串是321
		 * 所以需要把目前對應到的輸出先暫存起來，等讀到下一組數字再把這些數字的位置放到output對的地方
		 * 第一輪: 讀到3，tmp_ch = "參"，output = "參"
		 * 第二輪: 讀到2，tmp_ch = "貳拾"，output = "貳拾 參"
		 * 第三輪: 讀到1，tmp_ch = "壹佰"，output = "壹佰 貳拾 參"
		 * tmp_ch [0] = '\0'; 是偷懶的清空陣列的方法，其實沒有真的清空
		 * 只是第一個char即為結束符號，直接印出來會跟空字串效果一樣*/

		/* 接下來會用到sprintf()這個函式跟printf()很像，用法也幾乎一樣
		 * 差別在於他不把字串直接秀出來，而是把字串存到指定的陣列裡面
		 * 例如、我們要印出 hello world!，我們會寫printf("hello world!");
		 * 若不想直接印出來，而想存在某陣列 char out[50] 中的話，我們會寫sprintf(out, "hello world!");
		 * 到時候想印出這個字串時，就直接印出out字串 printf("%s", out); 即可*/

		/* 處理步驟一: 先找出目前讀到的數字對應的大寫中文字，將他暫存到tmp_ch中 */
		switch (input[i]) {
			case '0':
				//sprintf(tmp_ch, "零");
			break;
			case '1':
			sprintf(tmp_ch, "壹");
			break;
			case '2':
			sprintf(tmp_ch, "貳");
			break;
			case '3':
			sprintf(tmp_ch, "參");
			break;
			case '4':
			sprintf(tmp_ch, "肆");
			break;
			case '5':
			sprintf(tmp_ch, "伍");
			break;
			case '6':
			sprintf(tmp_ch, "陸");
			break;
			case '7':
			sprintf(tmp_ch, "柒");
			break;
			case '8':
			sprintf(tmp_ch, "捌");
			break;
			case '9':
			sprintf(tmp_ch, "玖");
			break;
			default:
			printf("輸入錯誤!\n");	// 只能輸入純數字字串，否則中斷
			system("pause");
			exit(1);
		}

		/* 處理步驟二: 填入對應的數字單位
		 * 判斷方法是(cnt_nu%4)，因為中文數字4個為一組，而"拾", "佰", "仟"這三個單位每一輪都會有，所以先挑出來處理
		 * 每一輪cnt_nu都要+1，所以迴圈尾端要cnt_nu++ */
		if ((cnt_nu%4) > 0) {
			if (input[i] != '0') {	/* 如果讀到數字'0'則該輪不輸出東西，所以(input[i] != '0')才繼續*/
				switch(cnt_nu%4) {
				/* 因為處理步驟一已經填好大寫數字了，所以這裡只要填上單位即可 */
					case 1: // 拾
					sprintf(tmp_ch, "%s拾", tmp_ch);
					break;
					case 2:// 佰
					sprintf(tmp_ch, "%s佰", tmp_ch);
					break;
					case 3:// 仟
					sprintf(tmp_ch, "%s仟", tmp_ch);
					break;
					default:
					printf("輸入錯誤!\n");
					system("pause");
					exit(1);
				}

				/* 到這裡已經處理完這一輪的tmp_ch了，接下來把它放到output中對的位置 */
				sprintf(output_tmp, "%s", output);
				sprintf(output, "%s%s", tmp_ch, output_tmp);
			}
		} else {	/* 如果單位不是"拾", "佰", "仟"，則處理步驟二跳到這裡 */
			if (i == (strlen(input) - 1)) {	/* 這是個位，所以後面沒有加單位 */
				sprintf(output, "%s", tmp_ch);	/* 直接放進output即可 */
			} else {	/* 如果不是個位，則每4個位數改變一次，定義在char su[MAX_SPECIAL_UNITS][3]這個陣列*/
				/* 用cnt_su紀錄目前對應單位的位置，每次+1，會用完所以若有更大的數字要處理，請示情況修改最上面定義的東西 */
				sprintf(tmp_ch, "%s%s", tmp_ch, su[cnt_su]);
				sprintf(output_tmp, "%s", output);
				sprintf(output, "%s%s", tmp_ch, output_tmp);
				cnt_su++;
			}
		}
		cnt_nu++;
	}

	/* 到這裡全部數字處理完畢，印出output */
	printf("output: %s\n", output);
	return 0;
}
