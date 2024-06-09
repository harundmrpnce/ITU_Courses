`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ITU Computer Engineering Department
// Engineer: Emre Bozkurt | Harun Yahya Demirpençe
// Project Name: BLG222E Project 1 
//////////////////////////////////////////////////////////////////////////////////

module ArithmeticLogicUnitSystem(
    RF_OutASel, RF_OutBSel, RF_FunSel, RF_RegSel, RF_ScrSel, ALU_FunSel, ALU_WF, 
    ARF_OutCSel, ARF_OutDSel, ARF_FunSel, ARF_RegSel, IR_LH, IR_Write, Mem_WR, Mem_CS,
    MuxASel, MuxBSel, MuxCSel, Clock
);
    input wire [2:0]  RF_OutASel, RF_OutBSel, RF_FunSel;
    input wire [3:0]  RF_RegSel, RF_ScrSel;
          wire [15:0] OutA, OutB;
          
    input wire [4:0]  ALU_FunSel;
    input wire        ALU_WF;
          wire [3:0]  FlagsOut;
          wire [15:0] ALUOut, Address;
          
    input wire [1:0]  ARF_OutCSel, ARF_OutDSel;
    input wire [2:0]  ARF_FunSel, ARF_RegSel;
          wire [15:0] OutC;
          
    input wire        IR_LH, IR_Write;
          wire [15:0] IROut;
          
    input wire        Mem_WR, Mem_CS;
          wire [7:0]  MemOut;
          
    input wire [1:0]  MuxASel, MuxBSel;
          reg  [15:0] MuxAOut, MuxBOut;
    input wire        MuxCSel;
          reg  [7:0]  MuxCOut;
    
    input wire        Clock;
    
    RegisterFile RF(
        .I(MuxAOut), .OutASel(RF_OutASel), .OutBSel(RF_OutBSel), 
        .FunSel(RF_FunSel), .RegSel(RF_RegSel), .ScrSel(RF_ScrSel), 
        .Clock(Clock), .OutA(OutA), .OutB(OutB)
    );
    ArithmeticLogicUnit ALU(
        .A(OutA), .B(OutB), .FunSel(ALU_FunSel), 
        .WF(ALU_WF), .Clock(Clock), .ALUOut(ALUOut), .FlagsOut(FlagsOut)
    );
    AddressRegisterFile ARF(
        .I(MuxBOut), .OutCSel(ARF_OutCSel), .OutDSel(ARF_OutDSel), 
        .FunSel(ARF_FunSel), .RegSel(ARF_RegSel), 
        .Clock(Clock), .OutC(OutC), .OutD(Address)
    );
    InstructionRegister IR(
        .I(MemOut), .Write(IR_Write), .LH(IR_LH), .Clock(Clock), .IROut(IROut)
    );
    Memory MEM(
        .Address(Address), .Data(MuxCOut), .WR(Mem_WR), .CS(Mem_CS), .Clock(Clock), .MemOut(MemOut)
    );

    always @* begin
        case (MuxASel)
            2'b00: MuxAOut <= ALUOut; // Select ALUOut[7:0]
            2'b01: MuxAOut <= OutC;     // Select ARF_OutC
            2'b10: MuxAOut <= {8'h00, MemOut}; // Select Memory Output, extend with zeros
            2'b11: MuxAOut <= {8'h00,IROut[7:0]};       // Select IR (7:0)
        endcase
    
        case (MuxBSel)
            2'b00: MuxBOut <= ALUOut; // Select ALUOut[15:8]
            2'b01: MuxBOut <= OutC;      // Select ARF_OutC
            2'b10: MuxBOut <= {8'h00, MemOut}; // Select Memory Output, extend with zeros
            2'b11: MuxBOut <= {8'h00,IROut[7:0]};        // Select IR (7:0)
        endcase
    
        case (MuxCSel)
            1'b0: MuxCOut <= ALUOut[7:0];  // Select ALUOut[7:0]
            1'b1: MuxCOut <= ALUOut[15:8]; // Select ALUOut[15:8]
        endcase
    end
endmodule