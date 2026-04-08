#include <gtest/gtest.h>

extern "C" {
    #include "lab4.h"
}


TEST(Lab4, Test1_CreateEmptyTree) {
    AVLTree tr;
    avlTreeCreate(&tr);
    ASSERT_EQ(tr.root, nullptr);
}

TEST(Lab4, Test2_InsertionAndBalance) {
    AVLTree tr;
    avlTreeCreate(&tr);
    
    tr.root = avlTreeInsert("a", 1, tr.root);
    tr.root = avlTreeInsert("b", 2, tr.root);
    tr.root = avlTreeInsert("c", 3, tr.root);
    
    ASSERT_NE(tr.root, nullptr);
    ASSERT_STREQ(tr.root->key, "b");
    ASSERT_EQ(tr.root->height, 2);
}

TEST(Lab4, Test3_SearchFunctionality) {
    AVLTree tr;
    avlTreeCreate(&tr);
    
    tr.root = avlTreeInsert("target", 228, tr.root);
    
    Node* found = avlTreeSearch("target", tr.root);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->value, 228);
    
    EXPECT_EQ(avlTreeSearch("missing", tr.root), nullptr);
}

TEST(Lab4, Test4_RemovalToEmpty) {
    AVLTree tr;
    avlTreeCreate(&tr);
    
    tr.root = avlTreeInsert("d", 4, tr.root);
    tr.root = avlTreeInsert("e", 5, tr.root);
    
    tr.root = avlTreeRemove("d", tr.root);
    ASSERT_NE(tr.root, nullptr);
    ASSERT_STREQ(tr.root->key, "e");
    
    tr.root = avlTreeRemove("e", tr.root);
    ASSERT_EQ(tr.root, nullptr);
}

TEST(Lab4, Test5_ComplexStructure) {
    AVLTree tr;
    avlTreeCreate(&tr);
    
    char* keys[] = {
        "alpha", "bravo", "charli", "delta", "echo", 
        "foxtro", "golf", "hotel", "india", "juliet",
        "kilo", "lima", "mike", "november", "oscar", 
        "papa", "quebec", "romeo", "sierra", "tango"
    };

    for (int i = 0; i < 20; i++) {
        tr.root = avlTreeInsert(keys[i], (double)i, tr.root);
    }

    ASSERT_NE(tr.root, nullptr);

    EXPECT_GE(tr.root->height, 4);
    EXPECT_LE(tr.root->height, 6);

    Node *n1 = avlTreeSearch("alpha", tr.root);
    Node *n2 = avlTreeSearch("tango", tr.root);
    Node *n3 = avlTreeSearch("kilo", tr.root);

    ASSERT_NE(n1, nullptr);
    ASSERT_NE(n2, nullptr);
    ASSERT_NE(n3, nullptr);

    EXPECT_DOUBLE_EQ(n1->value, 0.0);
    EXPECT_DOUBLE_EQ(n2->value, 19.0);
    EXPECT_DOUBLE_EQ(n3->value, 10.0);

    EXPECT_EQ(avlTreeSearch("zulu", tr.root), nullptr);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
