`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ITU Computer Engineering Department
// Engineer: Emre Bozkurt | Harun Yahya Demirpençe
// Project Name: BLG222E Project 1 
//////////////////////////////////////////////////////////////////////////////////

module ArithmeticLogicUnit(
        A, B, FunSel, WF, Clock, ALUOut, FlagsOut
    );
    input  wire [15:0]  A, B;
           reg  [15:0]  A_, B_;
           reg          Z, C, N, O;
           reg  [4:0]   MSB;
    input  wire [4:0]   FunSel;
    input  wire         Clock, WF;
    output reg  [15:0]  ALUOut;
    output reg  [3:0]   FlagsOut;   // ZCNO (MSB-LSB)  (Zero-Carry-Negative-Overflow)
    
    always@(*) begin
        A_= A;
        B_= B;
        {Z, C, N, O} = FlagsOut;
        MSB=4'b1111;
        if(!FunSel[4]) begin
            A_= {8'h00, A[7:0]};
            B_= {8'h00, B[7:0]};
            MSB= 4'b0111;
        end
        case(FunSel[3:0])
            4'b0000: 
                begin
                    ALUOut = A_;
                    N = ALUOut[MSB];
                end
            4'b0001: 
                begin
                    ALUOut = B_;
                    N = ALUOut[MSB];
                end
            4'b0010: 
                begin
                    ALUOut = ~A_;
                    N = ALUOut[MSB];
                end
            4'b0011: 
                begin
                    ALUOut = ~B_;
                    N = ALUOut[MSB];
                end
            4'b0100: 
                begin
                    {C, ALUOut} = {1'b0, A_} + {1'b0, B_};
                    N = ALUOut[MSB];
                    O = ((A_[MSB] == B_[MSB]) & (A_[MSB] != ALUOut[MSB]));
                end
            4'b0101: 
                begin
                    {C, ALUOut} = {1'b0, A_} + {1'b0, B_} + C;
                    N = ALUOut[MSB];
                    O = ((A_[MSB] == B_[MSB]) & (A_[MSB] != ALUOut[MSB]));
                end
            4'b0110: 
                begin
                    {C, ALUOut} = {1'b0, A_} + {1'b0, ~B_} + 1'b1;
                    C = ~C;
                    N = ALUOut[MSB];
                    O = ((ALUOut[MSB] == B_[MSB]) & (A_[MSB] != B_[MSB]));
                end
            4'b0111: 
                begin
                    ALUOut = A_ & B_;
                    N = ALUOut[MSB];
                end
            4'b1000: 
                begin
                    ALUOut = A_ | B_;
                    N = ALUOut[MSB];
                end
            4'b1001: 
                begin                      
                    ALUOut = A_ ^ B_;     
                    N = ALUOut[MSB]; 
                end
            4'b1010: 
                begin                      
                    ALUOut = ~(A_ & B_);   
                    N = ALUOut[MSB];
                end
            4'b1011: 
                begin                      // LOGICAL SHIFT LEFT
                    C = A_[MSB];
                    if(MSB==4'b1111) ALUOut = {A_[14:0], 1'b0};
                    else ALUOut = {A_[6:0], 1'b0};
                    N = ALUOut[MSB];
                end
            4'b1100: 
                begin                      // LOGICAL SHIFT RIGHT
                    C = A_[0];
                    if(MSB==4'b1111) ALUOut = {1'b0, A_[15:1]};
                    else ALUOut = {1'b0, A_[7:1]};
                    N = ALUOut[MSB]; 
                end
            4'b1101: 
                begin                      // ARITHMETIC SHIFT
                    C = A_[0];
                    if(MSB==4'b1111) ALUOut = {A_[15], A_[15:1]};
                    else ALUOut = {A_[7], A_[7:1]};
                end
            4'b1110: 
                begin                      // CIRCULAR SHIFT LEFT
                    if(MSB==4'b1111) ALUOut = {A_[14:0], C};
                    else ALUOut = {A_[6:0], C};
                    C = A_[MSB];
                    N = ALUOut[MSB];
                end
            4'b1111: 
                begin                      // CIRCULAR SHIFT RIGHT
                    if(MSB==4'b1111) ALUOut = {C, A_[15:1]};
                    else ALUOut = {C, A_[7:1]};
                    C = A_[0];
                    N = ALUOut[MSB];
                end
        endcase
        if(!FunSel[4]) begin
            ALUOut = {8'h00, ALUOut[7:0]};
        end
        Z = (ALUOut == 16'h0000);
    end

    always@(posedge Clock) begin
        if(WF) begin
            FlagsOut <= {Z,C,N,O};
        end
    end
endmodule