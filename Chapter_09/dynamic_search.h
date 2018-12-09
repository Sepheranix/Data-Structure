#pragma once

#include "my_type.h"
#include "tree.h"

BiTree SearchBST(BiTree T, KeyType key);
Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree &p);
Status InsertBST(BiTree &T, ElemType e);
Status DeleteBST(BiTree &T, KeyType key);
Status Delete(BiTree &p);