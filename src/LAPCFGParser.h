#ifndef AHCP_LAPCFG_PARSER_H_
#define AHCP_LAPCFG_PARSER_H_

#include "CKYTable.h"
#include "Dictionary.h"
#include "TagSet.h"
#include "Lexicon.h"
#include "Grammar.h"
#include "Tree.h"

#include <boost/multi_array.hpp>

#include <memory>
#include <string>
#include <vector>

namespace AHCParser {

class LAPCFGParser {

    LAPCFGParser();
    LAPCFGParser(const LAPCFGParser &) = delete;

public:
    ~LAPCFGParser();

    static std::shared_ptr<LAPCFGParser> loadFromBerkeleyDump(const std::string & path);

    std::shared_ptr<Tree<std::string> > parse(const std::vector<std::string> & sentence) const;

    Dictionary & getWordTable() { return *word_table_; }
    TagSet & getTagSet() { return *tag_set_; }
    Lexicon & getLexicon(int level) { return *(lexicon_[level]); }
    Grammar & getGrammar(int level) { return *(grammar_[level]); }

    double getPruningThreshold() const { return prune_threshold_; }
    void setPruningThreshold(double value);

    double getUNKLexiconSmoothing() const { return smooth_unklex_; }
    void setUNKLexiconSmoothing(double value);

private:
    std::shared_ptr<Dictionary> word_table_;
    std::shared_ptr<TagSet> tag_set_;
    std::vector<std::shared_ptr<Lexicon> > lexicon_;
    std::vector<std::shared_ptr<Grammar> > grammar_;

    double prune_threshold_;
    double smooth_unklex_;

    void loadWordTable(const std::string & path);
    void loadTagSet(const std::string & path);
    void loadLexicon(const std::string & path);
    void loadGrammar(const std::string & path);
    void generateCoarseModels();
    
    std::shared_ptr<Tree<std::string> > getDefaultParse() const;

    std::vector<int> makeWordIDList(const std::vector<std::string> & sentence) const;

    void initializeCharts(
        CKYTable<std::vector<bool> > & allowed,
        CKYTable<std::vector<double> > & inside,
        CKYTable<std::vector<double> > & outside,
        int cur_level) const;

    void setInsideScoresByLexicon(
        const CKYTable<std::vector<bool> > & allowed,
        CKYTable<std::vector<double> > & inside,
        const std::vector<int> & wid_list,
        int cur_level) const;

    void calculateInsideScores(
        const CKYTable<std::vector<bool> > & allowed,
        CKYTable<std::vector<double> > & inside,
        int cur_level) const;

    void calculateOutsideScores(
        const CKYTable<std::vector<bool> > & allowed,
        const CKYTable<std::vector<double> > & inside,
        CKYTable<std::vector<double> > & outside,
        int cur_level) const;

    void pruneCharts(
        CKYTable<std::vector<bool> > & allowed,
        const CKYTable<std::vector<double> > & inside,
        const CKYTable<std::vector<double> > & outside,
        int cur_level) const;

}; // struct Model

} // namespace AHCParser

#endif // AHCP_LAPCFG_PARSER_H_

