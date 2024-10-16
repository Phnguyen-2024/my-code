#include <bits/stdc++.h>
#define ElementType SINHVIEN
using namespace std;

typedef struct{
    string Ten;
    string Maso;
    float DTB;
} SINHVIEN;

typedef struct tagDNode{
    ElementType Info;
    struct tagDNode* pNext;
    struct tagDNode* pPrev;
}DNode;

typedef struct{
    DNode* pHead;
    DNode* pTail;
}DLIST;

void InitList(DLIST &L){
    L.pHead = NULL;
    L.pTail = NULL;
}

DNode *CreateDNode(SINHVIEN sv){
    DNode *tam;
    tam = new DNode;
    if(tam == NULL){
        cout << "Khong du bo nho";
        exit(1);
    }
    else{
        tam->Info = sv;
        tam->pNext = NULL;
        tam->pPrev = NULL;
        return tam;
    }
}

bool IsEmptyList(DLIST L){
    return L.pHead == NULL;
}

void AddFirst(DLIST &L, DNode *tam){
    if(L.pHead == NULL){
        L.pHead = tam;
        L.pTail = L.pHead;
    }
    else{
        tam->pNext = L.pHead;
        L.pHead->pPrev = tam;
        L.pHead = tam;
    }
}

void AddLast(DLIST &L, DNode *tam){
    if(L.pHead == NULL){
        L.pHead = tam;
        L.pTail = L.pHead;
    }
    else{
        tam->pPrev = L.pTail;
        L.pTail->pNext = tam;
        L.pTail = tam;
    }
}

void RemoveFirst(DLIST &L){
   DNode *p;
    if(L.pHead != NULL){
        p = L.pHead;
        L.pHead = L.pHead->pNext;
        if (L.pHead != NULL) {
            L.pHead->pPrev = NULL;
        } else {
            L.pTail = NULL;  
        }
        delete p;
    }
}

void RemoveLast(DLIST &L){
   DNode *p;
    if(L.pHead != NULL){
        p = L.pTail;
        L.pTail = L.pTail->pPrev;
        if(L.pTail != NULL){
            L.pTail->pNext = NULL;
        } else {
            L.pHead = NULL;  
        }
        delete p;
    }
}


string XepLoai(float DTB) {
    if (DTB <= 4.6) {
        return "Yeu";
    } 
    else if (DTB >= 5.0 && DTB < 6.5){
        return "Trung binh";
    } 
    else if (DTB >= 6.5 && DTB < 7.0){
        return "Trung binh kha";
    } 
    else if (DTB >= 7.0 && DTB < 8.0){
        return "Kha";
    } 
    else if (DTB >= 8.0 && DTB < 9.0){
        return "Gioi";
    } 
    else if (DTB >= 9.0){
        return "Xuat sac";
    } 
    else{
        return "Khong xac dinh";
    }
}

void PrintList(const DLIST &L) {
    DNode *p = L.pHead;
    while (p != NULL) {
        cout << "Ten: " << p->Info.Ten;
        cout << ", Ma so: " << p->Info.Maso;
        cout << ", DTB: " << p->Info.DTB;
        cout << ", Xep loai: " << XepLoai(p->Info.DTB) << endl;
        p = p -> pNext;
    }
}

DNode* SearchNode(DLIST &L, string &maso){
    if (IsEmptyList(L)) 
        return NULL;
    
    DNode *p = L.pHead;
    while(p != NULL){
        if (p->Info.Maso == maso) 
            return p;
        p = p->pNext;
    } 
    return NULL; 
}

    

int RemoveX(DLIST &L, string &maso){
    DNode *q = SearchNode(L, maso);
    if(q == NULL)
        return 0;
    if(q == L.pHead)
        RemoveFirst(L);
    else if(q == L.pTail){
        RemoveLast(L);
    }
    else{
        DNode* TruocQ = q ->pPrev;
        DNode* SauQ = q->pNext;
        TruocQ->pNext = SauQ;
        SauQ->pPrev = TruocQ;
        delete q;
    }
    return 1;
}

DLIST DanhsachsvcoDTBlonhonbangx(const DLIST &L, float x){
    DLIST kq;
    InitList(kq);
    DNode *p = L.pHead;
    
    if (IsEmptyList(L)) 
        return kq;

    do{
        if (p->Info.DTB >= x){
            DNode *newNode = CreateDNode(p->Info);
            AddLast(kq, newNode);
        }
        p = p->pNext;
    } while (p != NULL);
    
    return kq;
}


int main(){
    DLIST L;
    InitList(L);
    SINHVIEN sv;
    float x;
    int k;

    while (true) {
        cout << "Nhap ten sinh vien (nhap '0' de ket thuc): ";
        cin >> sv.Ten;
        if (sv.Ten == "0")
            break;
        cout << "Nhap ma so sinh vien: ";
        cin >> sv.Maso;
        cout << "Nhap diem trung binh: ";
        cin >> sv.DTB;
        cin.ignore();
        DNode *p = CreateDNode(sv);
        AddFirst(L, p);
    }

    cout << "Danh sach sinh vien: " << endl;
    PrintList(L);

    cout << "Nhap diem trung binh lon hon bang x: ";
    cin >> x;
    DLIST kq2 = DanhsachsvcoDTBlonhonbangx(L, x);
    if (IsEmptyList(kq2)){
        cout << "Khong co sinh vien nao co diem >= " << x << endl;
    } 
    else {
        cout << "Danh sach sinh vien co diem trung binh >= " << x << ": " << endl;
        PrintList(kq2);
        string maso;
        cout << "Nhap ma so sinh vien de xoa: ";
        cin >> maso;
        if (RemoveX(kq2, maso)) {
            cout << "Sinh vien voi ma so " << maso << " da duoc xoa." << endl;
        } else {
            cout << "Khong tim thay sinh vien voi ma so: " << maso << endl;
        }
        cout << "Danh sach sinh vien sau khi xoa: " << endl;
        PrintList(kq2);
    }
    return 0;
}
 
