#ifndef FINDHIGHLIGHTER_H
#define FINDHIGHLIGHTER_H

#include <QObject>
#include <QWidget>
#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QRegularExpression>
#include <QString>

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;
    QTextCharFormat findFormat;
    /////////////////////

public:
    Highlighter(QTextDocument *parent);
protected:
    void highlightBlock(const QString &text) override;
};

#endif // FINDHIGHLIGHTER_H
