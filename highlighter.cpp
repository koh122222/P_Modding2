#include "highlighter.h"
#include "allpar.h"
#include <QDebug>

Highlighter::Highlighter(QTextDocument *parent)
    :QSyntaxHighlighter(parent)
{
    ;
}

void Highlighter::updateHighLighter(const QString &text)
{
    highlightingRules.resize(0);
    //findFormat.setForeground(AllPar::highlighter_light[TYPE_MOD::EU_EVENTS]);
    //findFormat.setFontWeight(QFont::Bold);
    //findFormat.setBackground(Qt::green);
    for (int i = TYPE_MOD::EU_BEGIN; i < TYPE_MOD::END_TYPE; ++i)// : AllPar::highlighter_light)
    {
        findFormat.setForeground(AllPar::highlighter_light[i]);
        for (auto c : AllPar::modMap[i])
        {
            QString regExp = "";
            regExp += QStringLiteral("\\b") + c.first + QStringLiteral("\\b");
            highlightingRules.append(
                    HighlightingRule{QRegularExpression(regExp), findFormat});
        }
    }
    rehighlight();
}

void Highlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    setCurrentBlockState(0);
//////////! for {}
    /*
//! [8]

//! [9]
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

//! [9] //! [10]
    while (startIndex >= 0) {
//! [10] //! [11]
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
    */
}

