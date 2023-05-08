#include <stdio.h> //TU DIEN ANH-VIET - CAY NHI PHAN TIM KIEM
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

typedef struct Node{
    char ENG[26];
    char VIE[26];
    struct Node* leftChild;
    struct Node* rightChild;
}Node;
Node* root;

typedef struct String{
    char s[26];
}String;
String h[50];

Node* makeNode(char* eng, char* vie){
    Node* p = (Node*)malloc(sizeof(Node));
    strcpy(p->ENG, eng); 
    strcpy(p->VIE, vie);
    p->leftChild = NULL; 
    p->rightChild = NULL;
    return p;
}

Node* insert(Node* r, char* eng, char* vie){
    if(r == NULL) return makeNode(eng, vie);
    int c = strcmp(r->ENG, eng);
    if(c == 0){
        printf("Word \"%s\" exists, do not insert\n", eng); 
        return r;
    }else if(c < 0){
        r->rightChild = insert(r->rightChild, eng, vie); 
        return r;
    }else{
        r->leftChild = insert(r->leftChild, eng, vie); 
        return r;
    }
}

Node* find(Node* r, char* eng){
    if(r == NULL) return NULL;
    int c = strcmp(r->ENG, eng);
    if(c == 0) return r;
    if(c < 0){
        return find(r->rightChild, eng);
    }
    else return find(r->leftChild, eng);
}

void freeTree(Node* r){
    if(r == NULL) return;
    freeTree(r->leftChild);
    freeTree(r->rightChild);
    free(r);
}

void Init(){
    root = NULL;
}

void inOrder(Node* r){
    if(r == NULL) return;
    inOrder(r->leftChild);
    printf("%s %s\n",r->ENG, r->VIE);
    inOrder(r->rightChild);
}

void printFile(){
    FILE *f = fopen("dict.txt","r");
    while(!feof(f)){
        char eng[26], vie[26];
        fscanf(f, "%s %s", eng, vie);
        printf("%s %s\n", eng, vie);
    }
    fclose(f);
}

void printList(){
    inOrder(root);
    printf("\n");
}

void LoadFile(){
    FILE *f = fopen("dict.txt","r");
    while(!feof(f)){
        char eng[26], vie[26];
        fscanf(f, "%s %s", eng, vie);
        root = insert(root, eng, vie);
    }
    fclose(f);
}

void processInsert(){
    printf("Hay nhap tu tieng Anh: ");
    char eng[26], vie[26];
    scanf("%s", eng);
    if(find(root, eng) == NULL){
        printf("Hay nhap nghia cho tu nay: ");
        scanf("%s", vie);
        root = insert(root, eng, vie);
    }
    else{
        printf("Ban co muon nhap noi dung moi khong:(y/n): ");
        char choose;
        fflush(stdin);
        scanf("%c", &choose);
        while ((choose != 'y') && (choose != 'Y') && (choose != 'n') && (choose != 'N')){
            printf("Ban vui long chon lai:(y/n): ");
            fflush(stdin);
            scanf("%c", &choose);
        }
        if(choose == 'Y' || choose == 'y'){
            printf("Ban hay nhap noi dung moi: ");
            scanf("%s", vie);
            Node *tmp = find(root, eng);
            strcpy(tmp->VIE, vie);
        }
        else if(choose == 'N' || choose == 'n'){
            return;
        }
    }
}

void Translate(){
    char sentences[256], *p;
    printf("Hay nhap cau ban can dich: ");
    fflush(stdin);
    fgets(sentences, 256, stdin);
    sentences[strlen(sentences)-1] = '\0';
    int count = 0;
    p = strtok(sentences, " ");
    strcpy(h[count].s, strlwr(p));
    printf("%s\n", h[count].s);
    count++;
    while(p != NULL) {
        p = strtok(NULL, " ");
        if(p != NULL) {
            strcpy(h[count].s, strlwr(p));
            printf("%s\n", h[count].s);
            count++;
        }
    }
    char ans[256];
    Node *tmp = find(root, h[0].s);
    if(tmp == NULL){
        strcpy(ans, "<thieu tu>");
    }
    else{
        strcpy(ans, tmp->VIE);
    }
    for(int i = 1; i < count; i++){
        tmp = find(root, h[i].s);
        if(tmp == NULL){
            strcat(ans, " ");
            strcat(ans, "<thieu tu>");
        }
        else{
            strcat(ans, " ");
            strcat(ans, tmp->VIE);
        }  
    }
    printf("Cau sau khi dich la: %s\n", ans);
}

void Menu(){
    printf("\n--------MENU----------\n");
    printf("|1.Nap tu dien       |\n");
    printf("|2.Noi dung tu dien  |\n");
    printf("|3.Them/sua tu       |\n");
    printf("|4.Dich cau Anh-Viet |\n");
    printf("|5.Thoat             |\n");
    printf("----------------------\n");
    printf("Moi ban chon chuc nang: ");
}

int main(){
    Init();
    while(1){
        Menu();
        int k;
        scanf("%d", &k);
        while (k < 1 || k > 5){
            printf("Ban hay chon lai chuc nang(1->5): ");
            scanf("%d", &k);
        }
        switch (k)
        {
        case 1:
            LoadFile();
            printFile();
            break;
        case 2:
            printList();
            break;
        case 3:
            processInsert();
            break;
        case 4:
            Translate();
            break;
        case 5:
            freeTree(root);
            return 0;
        default:
            break;
        }
    }
    return 0;
}
