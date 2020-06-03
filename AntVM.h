#pragma once

#include <vector>
#include <stack>

namespace ant_vm
{
    ///////////////////////////////////////////////////////////
    // All instruction codes
    enum class InsCode {
        LOAD_CONST,
        LOAD_VAR,
        SET,
        ADD,
        SUB,
        MUL,
        DIV
    };

    ///////////////////////////////////////////////////////////
    // A Variable
    class Variable {
        double m_dValue;

    public:
        explicit Variable(const double& dValue = 0.0):
            m_dValue(dValue)
        {
        }

        void set(const double& dValue) {
            m_dValue = dValue;
        }

        double get() const {
            return m_dValue;
        }
    };

    ///////////////////////////////////////////////////////////
    // A single instruction
    struct Ins {
        InsCode m_iCode;
        union {
            double m_dConst;
            Variable* m_dVar;
        };

        explicit Ins(const InsCode& iCode):
            m_iCode(iCode),
            m_dConst(0.0)
        {
        }

        explicit Ins(const InsCode& iCode, const double& dConst):
                m_iCode(iCode),
                m_dConst(dConst)
        {
        }

        explicit Ins(const InsCode& iCode, Variable& dVar):
                m_iCode(iCode),
                m_dVar(&dVar)
        {
        }
    };

    ///////////////////////////////////////////////////////////
    // The Ant VM
    class AntVM {
        std::vector<Ins> m_vecInstructions;
        std::stack<double> m_S;

    public:
        explicit AntVM() = default;

        void addInstruction(const Ins&& ins)
        {
            m_vecInstructions.push_back(ins);
        }

        void clear()
        {
            m_S = std::stack<double>();
            m_vecInstructions.clear();
        }

        bool run()
        {
            for(auto& ins : m_vecInstructions)
            {
                switch (ins.m_iCode) {
                    case InsCode::LOAD_CONST:
                    {
                        const double& d1 = ins.m_dConst;
                        m_S.push(d1);
                        break;
                    }

                    case InsCode::LOAD_VAR:
                    {
                        const double& d1 = ins.m_dVar->get();
                        m_S.push(d1);
                        break;
                    }

                    case InsCode::SET:
                    {
                        const double& d1 = m_S.top();
                        ins.m_dVar->set(d1);
                        m_S.pop();
                        break;
                    }

                    case InsCode::ADD:
                    {
                        const double& d1 = m_S.top();
                        m_S.pop();

                        const double& d2 = m_S.top();
                        m_S.pop();

                        const double d3 = d1 + d2;
                        m_S.push(d3);

                        break;
                    }

                    case InsCode::SUB:
                    {
                        const double& d1 = m_S.top();
                        m_S.pop();

                        const double& d2 = m_S.top();
                        m_S.pop();

                        const double d3 = d2 - d1;
                        m_S.push(d3);

                        break;
                    }

                    case InsCode::MUL:
                    {
                        const double& d1 = m_S.top();
                        m_S.pop();

                        const double& d2 = m_S.top();
                        m_S.pop();

                        const double d3 = d1 * d2;
                        m_S.push(d3);

                        break;
                    }

                    case InsCode::DIV:
                    {
                        const double& d1 = m_S.top();
                        m_S.pop();

                        const double& d2 = m_S.top();
                        m_S.pop();

                        const double d3 = d2 / d1;
                        m_S.push(d3);

                        break;
                    }

                    default:
                        return false;
                }
            }

            //stack must be empty at the end of the run
            return m_S.empty();
        }
    };
}