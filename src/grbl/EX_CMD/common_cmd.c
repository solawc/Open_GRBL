
#include "common_cmd.h"


uint8_t system_excute_lg0_cmd(char *line) {

    char str_value[10];
    char *p;
    char *q;

    int letter;
    int count = 10;
    
    /*----------------------------------------------------------------------
      STEP 0:删除空格，将字母换成大写
    */
    collapseGCode(line);

    /*----------------------------------------------------------------------
      STEP 1: 查找LG0的标志
    */
    p = strstr(line, "LG0");

    if(p != NULL) { p = p + 3;  }
    else { return 100; }

    memset(str_value, '\0', sizeof(str_value));

    q = &str_value[0];

    /*----------------------------------------------------------------------
      STEP 2: 获取编号
    */
    while(*p != ']' && count != 0 && *p != '\0') {
      *q = *p;
      p++;
      q++;
      count--;
      if(count == 0 ) return 100; 
    }

    /*----------------------------------------------------------------------
      STEP 3: 获取参数
              TODO
    */

    letter = atof(str_value);

    switch(letter) {

      case 200:
        sd_report_state();
      break;

      case 201:
       sd_report_open_file(line);
      break;


      case 204:
        sd_report_mem();
      break;

      default:
        printReturnInfo("No this LG0 CMD\n");
      break;
      
    }

    return 0;  
}