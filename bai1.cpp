
#include <iostream>
#include <string>

using namespace std;

struct FileNode {
    long long size;      // Kich thuoc file tinh bang byte
    string address;      // Dia chi file
    string filename;     // Ten file
    long long timecopy;  // Thoi gian sao chep tinh bang giay
    FileNode* next;      // Con tro toi file tiep theo
};

struct List {
    FileNode* head;      
};

    // Khoi tao danh sach lien ket
void initList(List* list) {
    list->head = NULL;
}

   // Tao nut moi cho file
FileNode* taoFileNode(const string& address, const string& filename, long long size, long long timecopy) {
 
    FileNode* newNode = new FileNode;
    newNode->address = address;
    newNode->filename = filename;
    newNode->size = size;
    newNode->timecopy = timecopy;
    newNode->next = NULL;
    return newNode;
}

    // Chen nut file vao danh sach lien ket theo thoi gian sao chep
void insertFileNode(List* list, const string& address, const string& filename, long long size, long long timecopy) {
    FileNode* newNode = taoFileNode(address, filename, size, timecopy);
    FileNode* p = list->head;
    if (p == NULL || p->timecopy > timecopy) {
        newNode->next = p;
        list->head = newNode;
    } else {
        while (p->next != NULL && p->next->timecopy < timecopy) {
            p = p->next;
        }
        newNode->next = p->next;
        p->next = newNode;
    }
}

// Tinh tong kich thuoc cac file trong danh sach
long long tongkichthuoc(List* list) {
 
    long long totalSize = 0;
    FileNode* p = list->head;
    while (p != NULL) {
        totalSize += p->size;
        p = p->next;
    }
    return totalSize;
}

 // Sap xep danh sach theo kich thuoc file
void sortbySize(List* list) {
   
    if (list->head == NULL) return;

    List sortedList;
    initList(&sortedList);

    FileNode* p = list->head;
    while (p != NULL) {
        FileNode* node = p;
        p = p->next;

        if (sortedList.head == NULL || sortedList.head->size >= node->size) {
            node->next = sortedList.head;
            sortedList.head = node;
        } else {
            FileNode* current = sortedList.head;
            while (current->next != NULL && current->next->size < node->size) {
                current = current->next;
            }
            node->next = current->next;
            current->next = node;
        }
    }
    list->head = sortedList.head;
}

   // Xoa cac file co kich thuoc nho nhat de tong kich thuoc khong vuot qua maxSize
void deleteSmallestFiles(List* list, long long maxSize) {
 
    sortbySize(list);
    while (tongkichthuoc(list) > maxSize) {
        if (list->head == NULL) break;
        FileNode* toDelete = list->head;
        list->head = list->head->next;
        delete toDelete;
    }
}

// In ra danh sach cac file
void displayList(List* list) {
    FileNode* p = list->head;
    while (p != NULL) {
        cout << "File: " << p->filename << ", Size: " << p->size << " bytes, Time: " << p->timecopy << " seconds" << endl;
        p = p->next;
    }
}

int main() {
    List myList;
    initList(&myList);

    insertFileNode(&myList, "D:/Documents", "file3.txt", 500000, 1609459200);
    insertFileNode(&myList, "D:/Documents", "file1.txt", 200000, 1609545600);
    insertFileNode(&myList, "D:/Documents", "file2.txt", 300000, 1609632000);

    cout << "Files in the list:" << endl;
    displayList(&myList);

    long long totalSize = tongkichthuoc(&myList);
    cout << "Total size: " << totalSize << " bytes" << endl;

    long long maxSize = 32LL * 1024 * 1024 * 1024;
    deleteSmallestFiles(&myList, maxSize);

    cout << "Files after deletion to fit in 32GB USB:" << endl;
    displayList(&myList);

    return 0;
}
