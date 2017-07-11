#include <iostream>
#include <sstream>

bool IsWhitespace(char ch)
{
    if (ch == ' ' || ch == '\t')
    {
        return true;
    }
    
    return false;
}

bool IsAlpha(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        return true;
    }
    else if (ch >= 'a' && ch <= 'z')
    {
        return true;
    }
    
    return false;
}

class CSymbol
{
public:
    CSymbol(const std::string &str);
    virtual ~CSymbol();
    
    inline const std::string & GetData() const { return mv_strData; }
    
    virtual std::size_t TryParse(std::istream & strm);
    const CSymbol & operator = (const CSymbol & sm);
protected:
    std::string mv_strData;
};

CSymbol::CSymbol(const std::string & str) : mv_strData(str)
{
}

CSymbol::~CSymbol()
{
    
}

const CSymbol & CSymbol::operator = (const CSymbol & sym)
    {
        if (this != &sym)
        {
            mv_strData = sym.GetData();
        }
        
        return *this;
    }

std::size_t CSymbol::TryParse(std::istream & strm)
{
    mv_strData = "";
    
    std::size_t nCharsRead = 0;
    
    char ch = 0;
    
    bool bSym = false;
    
    while (strm.read(&ch, 1) == 1)
    {
        ++nCharsRead;
        
        if (bSym == true)
        {
            if (IsAlpha(ch) == true)
            {
                mv_strData += ch;
            }
            else
            {
                return nCharsRead;
            }
        }
        else if (IsWhitespace(ch) == true)
        {
            return nCharsRead;
        }
        else if (IsAlpha(ch) == true)
        {
            mv_strData += ch;
            bSym = true;
        }
        else
        {
            return nCharsRead;
        } 
    }
    
    return nCharsRead;
}

int main(int argc, char * argv[])
{
    std::stringstream myStream("James Schumacher is coding");
    
    CSymbol sym("");
    
    while (!myStream.eof())
    {
        sym.TryParse(myStream);
        
        if ( sym.GetData().length() != 0)
        {
            std::cout << "nSymbol: " << sym.GetData() << " ";        
        }
    }
    
     return 0;
}
