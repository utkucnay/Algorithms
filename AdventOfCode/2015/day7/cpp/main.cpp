#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using Wires = std::unordered_map<std::string, uint16_t>;
std::vector<std::string> SplitString(const std::string& inputs, char token = '\n');
bool is_number(const std::string& s);

template <typename Tp>
using Ref = std::shared_ptr<Tp>;

template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

class Instruction
{
public:
    Instruction(const std::string& wireResult) : m_wireResult(wireResult) {}
public:
    virtual void Run(Wires& wires) {}
    virtual bool HasWire(Wires& wires) { return true; }
    bool IsResultWire(const std::string& wireResult) { return wireResult == m_wireResult; }
protected:
    std::string m_wireResult;
};

class SetInstruction : public Instruction
{
public:
    SetInstruction(const std::string& wire, const std::string& wireResult) : m_wire(wire), Instruction(wireResult) {}

public:
    virtual void Run(Wires& wires) override;
    virtual bool HasWire(Wires& wires) override;

private:
    std::string m_wire;
};

class NotInstruction : public Instruction
{
public:
    NotInstruction(const std::string& wire, const std::string& wireResult) : m_wire(wire), Instruction(wireResult) {}

public:
    virtual void Run(Wires& wires) override;
    virtual bool HasWire(Wires& wires) override;

private:
    std::string m_wire;
};

class AndOrInstruction : public Instruction
{
public:
    enum GateType
    {
        And,
        Or
    };

public:
    AndOrInstruction(const std::string& wire0, GateType gateType, const std::string& wire1, const std::string& wireResult)
        : m_wire0(wire0), m_gateType(gateType), m_wire1(wire1), Instruction(wireResult) {}

public:
    virtual void Run(Wires& wires) override;
    virtual bool HasWire(Wires& wires) override;

private:
    GateType m_gateType;
    std::string m_wire0;
    std::string m_wire1;
};

class LRShiftInstruction : public Instruction
{
public:
    enum ShiftType : uint8_t
    {
        LShift,
        RShift
    };

public:
    LRShiftInstruction(const std::string& wire, ShiftType shiftType, uint16_t shiftCount, const std::string& wireResult)
        : m_wire(wire), m_shiftType(shiftType), m_shiftCount(shiftCount),  Instruction(wireResult)  {}

public:
    virtual void Run(Wires& wires) override;
    virtual bool HasWire(Wires& wires) override;

private:
    ShiftType m_shiftType;
    uint16_t m_shiftCount;
    std::string m_wire;
};

std::list<Ref<Instruction>> GetInstructions(const std::string& path);
void RunInstructions(std::list<Ref<Instruction>> instructions, Wires& wires);
void EraseInstructionForResultWire(std::list<Ref<Instruction>>& instructions, const std::string& wireResult);
void SetWire(Wires& wires);

int main()
{
    Wires wires;
    SetWire(wires);

    auto instructions = GetInstructions("input.txt");
    RunInstructions(instructions, wires);

    std::cout << wires["a"] << std::endl;

    int aWire = wires["a"];

    wires.clear();
    SetWire(wires);
    wires["b"] = aWire;

    EraseInstructionForResultWire(instructions, "b");
    RunInstructions(instructions, wires);

    std::cout << wires["a"] << std::endl;
}

void EraseInstructionForResultWire(std::list<Ref<Instruction>>& instructions, const std::string& wireResult)
{
    auto bIndex = std::find_if(instructions.begin(), instructions.end(), [] (Ref<Instruction> ins)
            {
                return ins->IsResultWire("b");
            });
    instructions.erase(bIndex);
}

void SetWire(Wires& wires)
{
    for(uint16_t i = 0; i < std::numeric_limits<uint16_t>::max(); i++)
        wires[std::to_string(i)] = i;
}

std::list<Ref<Instruction>> GetInstructions(const std::string& path)
{
    std::ifstream ifstr;
    ifstr.open(path);
    std::string input(std::istreambuf_iterator<char>(ifstr), {});

    std::list<Ref<Instruction>> instructions;

    std::vector<std::string> sInput = SplitString(input);
    sInput.erase(sInput.end() - 1);
    for (std::string& instructionString : sInput)
    {
        std::vector<std::string> insSStr = SplitString(instructionString, ' ');

        if(insSStr.size() == 3)
        {
            instructions.push_back((CreateRef<SetInstruction>(insSStr.at(0), insSStr.at(2))));
        }
        else if(insSStr.size() == 4)
        {
            instructions.push_back((CreateRef<NotInstruction>(insSStr.at(1), insSStr.at(3))));
        }
        else if(insSStr.at(1).at(0) == 'A')
        {
            instructions.push_back((CreateRef<AndOrInstruction>(insSStr.at(0), AndOrInstruction::GateType::And, insSStr.at(2), insSStr.at(4))));
        }
        else if(insSStr.at(1).at(0) == 'O')
        {
            instructions.push_back((CreateRef<AndOrInstruction>(insSStr.at(0), AndOrInstruction::GateType::Or, insSStr.at(2), insSStr.at(4))));
        }
        else if(insSStr.at(1).at(0) == 'L')
        {
            instructions.push_back((CreateRef<LRShiftInstruction>(insSStr.at(0), LRShiftInstruction::LShift, std::stoi(insSStr.at(2)), insSStr.at(4))));
        }
        else if(insSStr.at(1).at(0) == 'R')
        {
            instructions.push_back((CreateRef<LRShiftInstruction>(insSStr.at(0), LRShiftInstruction::RShift, std::stoi(insSStr.at(2)), insSStr.at(4))));
        }
        else
        {
            std::cout << "Failed Encoded Instructions" << instructionString << std::endl;
        }
    }

    ifstr.close();

    std::cout << "Instruction Setted" << std::endl;
    return instructions;
}

void RunInstructions(std::list<Ref<Instruction>> instructions, Wires& wires)
{
    while(instructions.size() > 0)
    {
        std::list<Ref<Instruction>> tInstructions;
        for(auto i = instructions.begin(); i != instructions.end(); std::advance(i, 1))
        {
            if((*i)->HasWire(wires))
            {
                (*i)->Run(wires);
            }
            else
            {
                tInstructions.push_back(std::move(*i));
            }
        }
        instructions.swap(tInstructions);
    }
}

void SetInstruction::Run(Wires& wires)
{
    wires[m_wireResult] = wires[m_wire];
}

bool SetInstruction::HasWire(Wires& wires)
{
    return wires.find(m_wire) != wires.end();
}

void NotInstruction::Run(Wires& wires)
{
    wires[m_wireResult] = ~wires[m_wire];
}

bool NotInstruction::HasWire(Wires& wires)
{
    return wires.find(m_wire) != wires.end();
}

void AndOrInstruction::Run(Wires& wires)
{
    switch (m_gateType)
    {
        case GateType::Or:
            wires[m_wireResult] = wires[m_wire0] | wires[m_wire1];
            break;
        case GateType::And:
            wires[m_wireResult] = wires[m_wire0] & wires[m_wire1];
            break;
    }
}

bool AndOrInstruction::HasWire(Wires& wires)
{
    return (wires.find(m_wire0) != wires.end()) && (wires.find(m_wire1) != wires.end());
}

void LRShiftInstruction::Run(Wires& wires)
{
    switch (m_shiftType)
    {
        case ShiftType::LShift:
            wires[m_wireResult] = wires[m_wire] << m_shiftCount;
            break;
        case ShiftType::RShift:
            wires[m_wireResult] = wires[m_wire] >> m_shiftCount;
            break;
    }
}

bool LRShiftInstruction::HasWire(Wires& wires)
{
    return wires.find(m_wire) != wires.end();
}

std::vector<std::string> SplitString(const std::string& inputs, char token)
{
    std::vector<std::string> result;
    std::stringstream ss;

    for(char input : inputs)
    {
        if(input != token)
            ss << input;
        else
        {
            result.push_back(ss.str());
            ss.str("");
        }
    }

    result.push_back(ss.str());
    return result;
}

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
