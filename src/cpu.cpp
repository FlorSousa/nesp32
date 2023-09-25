#include <stack>

class Cpu {
    public:
        bool Z;
        bool N;
        bool C;
        bool V;
        bool I;
        bool D;
        bool B;
        bool U;
        int  X;
        int  Y;
        int  A;
        int  P;
        int  PC;
        int  SP;
        std::stack<int> Stack;

        void setPC(int value) {
            this->PC = value;
        }
        int getPC() {
            return this->PC;
        }

        void setSP(int value) {
            this->SP = value;
        }
        int getSP() {
            return this->SP;
        }

        void setX(int value) {
            this->X = value;
        }
        int getX() {
            return this->X;
        }
        void setY(int value) {
            this->Y = value;

        }
        int getY() {
            return this->Y;
        }

        void setA(int value) {
            this->A = value;
        }
        int getA() {
            return this->A;
        }

        void setZ(bool value) {
            this->Z = value;
        }
        bool getZ() {
            return this->Z;
        }

        void setN(bool value) {
            this->N = value;
        }
        bool getN() {
            return this->N;
        }

        void setC(bool value) {
            this->C = value;
        }
        bool getC() {
            return this->C;
        }

        void setV(bool value) {
            this->V = value;
        }
        bool getV() {
            return this->V;
        }

        void setI(bool value) {
            this->I = value;
        }
        bool getI() {
            return this->I;
        }

        void setD(bool value) {
            this->D = value;
        }
        bool getD() {
            return this->D;
        }

        void setB(bool value) {
            this->B = value;
        }
        bool getB() {
            return this->B;
        }

        void setU(bool value) {
            this->U = value;
        }
        bool getU() {
            return this->U;
        }

        int getStackValue() {
            if (!this->Stack.empty() && this->SP >= 0 && this->SP < this->Stack.size()) {
                std::stack<int> tempStack = Stack;

                int index = Stack.size() - 1;
                while (index > this->SP) {
                    tempStack.pop();
                    index--;
                }

                return tempStack.top();
            }
            return -1;
        }
    
        void pushStack(int value){
            this->Stack.push(value);
        }

        //implied
        void BRK_impl() {
            //break
            //this->I = 1;
        }

        
        void CLC_impl() {
            //clear carry
            this->C = false;
        }

        void CLD_impl() {
            //clear decimal mode
            this->D = false;
        }

        void CLI_impl() {
            //clear Interrupt Disable Bit
            this->I = false;
        }

        void CLV_impl() {
            //clear Overflow Flag
            this->V = false;
        }

        void DEX_impl() {
            //decrement Index X by One
            this->X -= 1;
        }

        void DEY_impl() {
            //decrement Index Y by One
            this->Y -= 1;
        }

        void INX_impl() {
            //Increment Index X by One
            this->X += 1;
        }
        void INY_impl() {
            //Increment Index Y by One
            this->Y += 1;
        }

        void NOP_impl() {
            //No Operation
        }

        void SEC_impl() {
            //set Carry Flag
            this->C = true;
        }

        void SED_impl() {
            //set Decimal Flag
            this->D = true;
        }

        void SEI_impl() {
            //set Interrupt Disable
            this->I = true;
        }

        void TAX_impl() {
            //Transfer Accumulator to Index X
            this->X = this-> A;
        }

        void TAY_impl() {
            //Transfer Accumulator to Index Y
            this->Y = this-> A;
        }

        void TSX_impl() {
            //Transfer Stack Pointer to Index X
            this->X = this-> SP;
            
        }

        void TXA_impl() {
            //Transfer Index X to Accumulator
            this->A = this-> X;
        }

        void TXS_impl() {
            //Transfer Index X to Stack Register
            this->SP = this->X;
        }

        void TYA_impl() {
            //Transfer Index Y to Accumulator
            this->A = this->Y;
        }
        void RTI_implied(){
            //Return from Interrupt
        }
        void RTS_implied(){}

        //immediate

        void ADC_imm(int value) {
            //Add Memory to Accumulator with Carry
            if(this->C){
                this->A = value + 1;
                return;
            }  
            this->A = value;
        }

        void AND_imm(int value) {
            //AND Memory with Accumulator
            this->A = this->A & value;
        }

        void CMP_imm(int value) {
            int result = this->A - value;
            if(result>0){
                this->C = true;
                this->N = false;
                this->Z = false;
                return;
            }

            if(result<0){
                this->C = false;
                this->N = true;
                this->Z = false;
                return;
            }

            this->C = true;
            this->N = false;
            this->Z = true;
            return;
        }

        void CPX_imm(int value) {
            int result = this->X - value;
            if(result>0){
                this->C = true;
                this->N = false;
                this->Z = false;
                return;
            }

            if(result<0){
                this->C = false;
                this->N = true;
                this->Z = false;
                return;
            }

            this->C = true;
            this->N = false;
            this->Z = true;
            return;
        }

        void CPY_imm(int value) {
            int result = this->Y - value;
            if(result>0){
                this->C = true;
                this->N = false;
                this->Z = false;
                return;
            }

            if(result<0){
                this->C = false;
                this->N = true;
                this->Z = false;
                return;
            }

            this->C = true;
            this->N = false;
            this->Z = true;
            return;
        }

        void EOR_imm(int value) {
            this->A = this->A ^ value;
            if(this->A < 0){
                this->N = true;
                this->Z = false;
                return;
            }

            if(this->A ==0){
                this->N = false;
                this->Z = true;
                return;
            }
        }

        void LDA_imm(int value) {
            this->A = value;
            if(value > 0){
                this->Z = 0;
                this->N = 0;
                return;
            }
            if(value<0){
                this->Z = 0;
                this->N = 1;
                return;
            }

            if(value == 0){
                this->Z = 1;
                this->N = 0;
                return;
            }
        }

        void LDX_imm(int value) {

        }
        void LDY_imm(int value) {}
        void ORA_imm(int value) {}
        void SBC_imm(int value) {}

        //zero page
        void ORA_zero_page(){}
        void ASL_zero_page(){}
        void ORA_zero_page_X(){}
        void ASL_zero_page_X(){}
        void ORA_zero_page_X(){}
        void ASL_zero_page_X(){}
        void BIT_zero_page(){}
        void AND_zero_page(){}
        void ROL_zero_page(){}
        void AND_zero_page_X(){}
        void ROL_zero_page_X(){}
        void EOR_zero_page(){}
        void LSR_zero_page(){}
        void EOR_zero_page_X(){}
        void LSR_zero_page_X(){}
        void ADC_zero_page(){}
        void ROR_zero_page(){}
        void ADC_zero_page_X(){}
        void ROR_zero_page_X(){}
        void STA_zero_page(){}
        void STY_zero_page(){}
        void STA_zero_page_X(){}
        void STX_zero_page(){}
        void LDY_zero_page(){}
        void LDA_zero_page(){}
        void LDX_zero_page(){}
        void CPY_zero_page(){}
        void CMP_zero_page(){}
        void DEC_zero_page(){}
        void CMP_zero_page_X(){}
        void DEC_zero_page_X(){}
        void CPX_zero_page(){}
        void SBC_zero_page(){}
        void INC_zero_page(){}
        void SBC_zero_page_X(){}
        void INC_zero_page_X(){}

        //absolute
        void ORA_absolute(){}
        void ASL_absolute(){}
        void ORA_absolute_Y(){}
        void ORA_absolute_X(){}
        void ASL_absolute_X(){}
        void ORA_absolute_Y(){}
        void ORA_absolute_X(){}
        void ASL_absolute_X(){}
        void AND_absolute_Y(){}
        void AND_absolute_X(){}
        void ROL_absolute_X(){}
        void BIT_absolute(){}
        void AND_absolute(){}
        void ROL_absolute(){}
        void EOR_absolute(){}
        void LSR_absolute(){}
        void EOR_absolute_Y(){}
        void EOR_absolute_X(){}
        void LSR_absolute_X(){}
        void ADC_absolute(){}
        void ROR_absolute(){}
        void JSR_absolute(){}
        void ADC_absolute_Y(){}
        void ADC_absolute_X(){}
        void ROR_absolute_X(){}
        void STY_absolute(){}
        void STA_absolute(){}
        void STX_absolute(){}
        void STY_absolute_X(){}
        void STA_absolute_Y(){}
        void STX_absolute_Y(){}
        void LDY_absolute(){}
        void LDA_absolute(){}
        void LDX_absolute(){}
        void LDY_absolute_X(){}
        void LDA_absolute_Y(){}
        void LDX_absolute_Y(){}
        void CPY_absolute(){}
        void CMP_absolute(){}
        void DEC_absolute(){}
        void CMP_absolute_X(){}
        void DEC_absolute_X(){}
        void CPX_absolute(){}
        void SBC_absolute(){}
        void INC_absolute(){}
        void CMP_absolute_Y(){}

        //relative
        void BPL_relative(){}
        void BMI_relative(){}
        void BVC_relative(){}
        void BVS_relative(){}
        void BCC_relative(){}
        void BCS_relative(){}
        void BNE_relative(){}
        void BEQ_relative(){}
        void BCC_relative(){}
        void BCS_relative(){}
        void BNE_relative(){}
        void BEQ_relative(){}

        //indirect
        void ORA_X_indirect(){}
        void ORA_indirect_Y(){}
        void ORA_indirect_Y(){}
        void BIT_indirect_Y(){}
        void EOR_X_indirect(){}
        void EOR_indirect_Y(){}
        void ADC_X_indirect(){}
        void ADC_indirect_Y(){}
        void STA_X_indirect(){}
        void LDA_X_indirect(){}
        void CMP_X_indirect(){}
        void CMP_indirect_Y(){}
        void SBC_X_indirect(){}
        void SBC_indirect_Y(){}
};