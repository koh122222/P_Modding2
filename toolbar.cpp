#include "toolbar.h"

/*
 * NEW_FILE,
        OPEN_FILE,
        SAVE_FILE,
        SAVE_ALL_FILE,
        CLOSE_FILE,
        CLOSE_ALL_FILE, ///////RASDELITEL
        CUT_TEXT,
        COPY_TEXT,
        PASTE_TEXT,
        BACK_TEXT,
        FORWARD_TEXT,
        FIND_TEXT,
        REPLACE_WORD,
        INCREASE_TEXT,
        REDUCE_TEXT
 */
ToolBar::ToolBar(QWidget* parent)
    :QToolBar(parent)
{
    allActionButton.push_back(addAction(QIcon("://resources//toolIcon//icon_openFile.png"), "open (?)"));
    allActionButton.push_back(addAction(QIcon("://resources//toolIcon//icon_save.png"), "save (Crtl + S)"));
    allActionButton.push_back(addAction(QIcon("://resources//toolIcon//icon_saveAllFile.png"), "save all (?)"));
    allActionButton.push_back(addAction(QIcon("://resources//toolIcon//icon_closeFile.png"), "close (?)"));
    allActionButton.push_back(addAction(QIcon("://resources//toolIcon//icon_closeAllFile.png"), "close all (?)"));
    addSeparator();
    allActionButton.push_back(addAction(QIcon("://resources//toolIcon//icon_cutText.png"), "cut (crtl + X)"));
    allActionButton.push_back(addAction(QIcon("://resources//toolIcon//icon_copyText.png"), "copy (crtl + C)"));
    allActionButton.push_back(addAction(QIcon("://resources//toolIcon//icon_pasteText.png"), "paste (crtl + V)"));
    addSeparator();
    allActionButton.push_back(addAction(QIcon("://resources//toolIcon//icon_backText.png"), "back (crtl + Z)"));
    allActionButton.push_back(addAction(QIcon("://resources//toolIcon//icon_forwardText.png"), "forward (crtl + Y)"));
    addSeparator();
    allActionButton.push_back(addAction(QIcon("://resources//toolIcon//icon_findText.png"), "find (crtl + F)"));
    allActionButton.push_back(addAction(QIcon("://resources//toolIcon//icon_replaceWord.png"), "replace (?)"));
    addSeparator();
    allActionButton.push_back(addAction(QIcon("://resources//toolIcon//icon_increaseText.png"), "increase (crtl + mouse wheel forward)"));
    allActionButton.push_back(addAction(QIcon("://resources//toolIcon//icon_reduceText.png"), "reduce (crtl + mouse wheel backward)"));

    setMaximumHeight(32);









    //allActionButton.push_back(addAction(QIcon("://resources//toolIcon//"), ""));

    //://resources//
}