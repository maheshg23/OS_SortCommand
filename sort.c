#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"

char buf[1024];
char minStr[1024];
char temp[1024];

int strcompare(char *str1,char *str2){

    int cmp =-1;
    int i;
    if(strcmp(str1,str2) == 0) return 0;
    for(i = 0; i < strlen(str1); i++){
        int a = (int) str1[i];
        int b = (int) str2[i];  
        //int n = 0;
        if(a-b == 32 || b-a == 32){
            if(cmp == -1)
                cmp = a < b ? 1 : -1; //str2 : str1;
        }
        else if (a-b != 0){
            if(a>=65 && a<97) a = a + 32;
            if(b>=65 && b<97) b = b + 32;
            cmp = b < a ? 1 : -1; //str2 : str1;
            break;
        }
    }
    return cmp;
}
       
void sortStrings(char *arr[], int n){
    int i, j, min_idx;

    for (i = 0; i < n-1; i++){
        min_idx = i;
        strcpy(minStr, arr[i]);
        for (j = i+1; j < n; j++){
            //if (strcmp(minStr, arr[j]) > 0)
            if (strcompare(minStr, arr[j]) > 0){
                strcpy(minStr, arr[j]);
                min_idx = j;
            }
        }

        if (min_idx != i){
          strcpy(temp, arr[i]);
          strcpy(arr[i], arr[min_idx]);
          strcpy(arr[min_idx], temp);
        }
    }
}

int ft_atoi(char *str){
    int i = 0;
    int sign = 1;
    int val = 0;

    while (str[i] == '-') {
        sign = -sign;
        i++;
    }
    while(str[i] >= '0' && str[i] <= '9'){
        int nbr = (int) (str[i] - '0');
        val = (val * 10) + nbr;
        i++;
    }
    return (val * sign);
}

void sortNumbers(char *arr[], int n){
    int i, j;
    char *key;
    for (i = 1; i < n; i++){
        key = arr[i];
        j = i - 1;
        while (j >= 0 && ft_atoi(arr[j]) > ft_atoi(key)){
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
 }

// void readFromFileAndSort(int fd){
void readFromFileAndSort(int inputfd, char *inputfilename, int outputfd, char *outputfilename, int isnumbers, int doreverse){
    int i = 0;
    int j = 0;
    int k = 0;
    int n;

    char *nums[512];
    char *temp = (char *) malloc(1024*sizeof(char));

    while((n = read(inputfd, buf, sizeof(buf))) > 0){
        for(i=0; i<n; i++){
            if(buf[i] != '\n'){
              temp[j++] = buf[i];
            }
            else{
                nums[k] = temp;
                temp = (char *) malloc(1024*sizeof(char));
                j=0;
                k++;
            }
        }
    }

    if(isnumbers == 1)
        sortNumbers(nums,k);   
    else
        sortStrings(nums,k);

    //normal
    if(doreverse != 1)
        {
            for(i = 0 ; i < k ; i++){
                if(write(outputfd, nums[i], strlen(nums[i])) != strlen(nums[i])) {
                printf(2, "sort: write error\n");
                exit();
                }
                if(write(outputfd, "\n", 1) != 1) {
                printf(2, "sort: write error\n");
                exit();
                }
            }   
        }
    //reverse
    if(doreverse == 1){ 
        for(i = k-1 ; i >= 0 ; i--){
            if(write(outputfd, nums[i], strlen(nums[i])) != strlen(nums[i])) {
                printf(2, "sort: write error\n");
                exit();
            }
            if(write(outputfd, "\n", 1) != 1) {
                printf(2, "sort: write error\n");
                exit();
            }
        }
    }
}

int main(int argc, char *argv[]){
    int fd;
    if(argc <= 1){
        readFromFileAndSort(0, "", 1, "", 0, 0);
        exit();
    }
    else if(argc == 2){
        if((fd = open(argv[1], 0)) < 0){
            printf(1, "cannot open file %s\n", argv[1]);
            exit();
        }
        // readFromFileAndSort(fd);
        //readFromFileAndSort(fd, argv[1], fd1, argv[1], 0);
        readFromFileAndSort(fd, argv[1], 1, "", 0, 0);
        close(fd);
    }
    else if(argc > 6){
        int i;
        char *nums[argc-1];
        for(i = 0 ; i < argc-1 ; i++)
            nums[i] = argv[i+1];

        sortStrings(nums,argc-1);

        for(i = 0 ; i < argc-1 ; i++){
            if(write(1, nums[i], strlen(nums[i])) != strlen(nums[i])) {
                printf(2, "sort: write error\n");
                exit();
            }
            if(write(1, "\n", 1) != 1) {
                printf(2, "sort: write error\n");
                exit();
            }
        }
    }   
    else{
        int numbers = 0;
        int reverse = 0;
        char *outputfilename = "";
        char *inputfilename = "";
        int outfd=0;
        int infd=0;
        int ops = 1;
        
        for(ops = 1; ops <= argc; ops++){
            char *operation = argv[ops];
            if(strcmp(operation, "-o") == 0){
                 outputfilename = argv[++ops];
                 inputfilename = argv[ops+1];

                 if((outfd = open(outputfilename, O_CREATE | O_WRONLY)) < 0){
                     printf(1, "cannot open output file %s\n", outputfilename);
                     exit();
                 }
            }
            if(strcmp(operation, "-r") == 0){
                  reverse = 1;
                  inputfilename = argv[ops+1]; 
            }
            if(strcmp(operation, "-n")==0){
                numbers = 1;
                inputfilename = argv[ops+1]; 
            }
        }

        if((infd = open(inputfilename, 0)) < 0){
             printf(1, "cannot input open file %s\n", inputfilename);
             exit();
        }

        readFromFileAndSort(infd, inputfilename, outfd, outputfilename, numbers, reverse);

        close(infd);
        close(outfd);
    }
    exit();
}