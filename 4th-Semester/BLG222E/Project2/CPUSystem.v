`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ITU Computer Engineering Department
// Engineer: Emre Bozkurt | Harun Yahya Demirpençe
// Project Name: BLG222E Project 2
//////////////////////////////////////////////////////////////////////////////////


module CPUSystem(
    Clock, Reset, T
);
    input  wire        Clock, Reset;
    output reg  [7:0]  T = 8'h00;
           reg  [2:0]  RF_OutASel, RF_OutBSel, RF_FunSel;
           reg  [3:0]  RF_RegSel, RF_ScrSel;
           reg  [4:0]  ALU_FunSel;
           reg  [1:0]  ARF_OutCSel, ARF_OutDSel;
           reg  [2:0]  ARF_FunSel, ARF_RegSel;
           reg         IR_LH, IR_WR;
           reg         Mem_WR, Mem_CS;
           reg  [1:0]  MuxASel, MuxBSel;
           reg         MuxCSel;
           
           
    ArithmeticLogicUnitSystem  _ALUSystem(
        .RF_OutASel(RF_OutASel), .RF_OutBSel(RF_OutBSel), .RF_FunSel(RF_FunSel), .RF_RegSel(RF_RegSel), .RF_ScrSel(RF_ScrSel), 
        .ALU_FunSel(ALU_FunSel), .ALU_WF(_ALUSystem.IR.IROut[9]),
        .ARF_OutCSel(ARF_OutCSel), .ARF_OutDSel(ARF_OutDSel), .ARF_FunSel(ARF_FunSel), .ARF_RegSel(ARF_RegSel), 
        .IR_LH(IR_LH), .IR_Write(IR_WR), 
        .Mem_WR(Mem_WR), .Mem_CS(Mem_CS),
        .MuxASel(MuxASel), .MuxBSel(MuxBSel), .MuxCSel(MuxCSel), 
        .Clock(Clock)
    );

    task Clean;
        begin
            RF_FunSel = 3'b011;
            RF_ScrSel = 4'h0;
        end
    endtask

    initial begin
        _ALUSystem.ARF.PC.Q = 16'h0000;
        _ALUSystem.RF.R1.Q = 16'h0000;
        _ALUSystem.RF.R2.Q = 16'h0000;
        _ALUSystem.RF.R3.Q = 16'h0000;
        _ALUSystem.RF.R4.Q = 16'h0000;
        _ALUSystem.RF.S1.Q = 16'h0000;
        _ALUSystem.RF.S2.Q = 16'h0000;
        _ALUSystem.RF.S3.Q = 16'h0000;
        _ALUSystem.RF.S4.Q = 16'h0000;
        RF_RegSel = 4'hF;
        RF_ScrSel = 4'hF;
        ARF_RegSel = 3'b111;
        Mem_CS = 1'b1;
    end
    
    always @(posedge Clock) begin
        case(T) 
            8'h00: // t0
                begin
                    ARF_OutDSel = 2'b00;
                    Mem_CS = 1'b0;
                    Mem_WR = 1'b0;
                    IR_WR = 1'b1;
                    IR_LH = 1'b0;
                    ARF_RegSel = 3'b011;
                    ARF_FunSel = 3'b001;
                    T = 8'h01;
                end
            8'h01: //t1
                begin
                    IR_LH = 1'b1;
                    ARF_RegSel = 3'b011;
                    ARF_FunSel = 3'b001;
                    T = 8'h02;
                end
            8'h02:  //t2
                begin
                    ARF_RegSel = 3'b111;
                    ARF_FunSel = 3'b010;
                    Mem_CS = 1'b1;
                    IR_WR = 1'b0;
                    T = 8'h04;
                end
            8'h04:  //t3
                begin
                    case(_ALUSystem.IR.IROut[15:10])
                        6'h00:
                            begin
                                MuxASel = 2'b11;
                                RF_ScrSel = 4'h7;
                                RF_FunSel = 3'b010;
                                T = 8'h08;
                            end
                        6'h01:
                            begin
                                if (_ALUSystem.ALU.FlagsOut[3] == 0) begin
                                    MuxASel = 2'b11;
                                    RF_ScrSel = 4'h7;
                                    RF_FunSel = 3'b010;
                                    T = 8'h08;
                                end
                                else begin
                                    Clean;
                                    T = 8'h00;
                                end
                            end
                        6'h02:
                            begin
                                if (_ALUSystem.ALU.FlagsOut[3] == 1) begin
                                    MuxASel = 2'b11;
                                    RF_ScrSel = 4'h7;
                                    RF_FunSel = 3'b010;
                                    T = 8'h08;
                                end
                                else begin
                                    Clean;
                                    T = 8'h00;
                                end
                            end
                        6'h03:
                            begin
                                ARF_OutDSel = 2'b11;
                                Mem_CS = 1'b0;
                                Mem_WR = 1'b0;
                                MuxASel = 2'b10;
                                case(_ALUSystem.IR.IROut[9:8])
                                    2'b00: RF_RegSel = 4'h7;
                                    2'b01: RF_RegSel = 4'hB;
                                    2'b10: RF_RegSel = 4'hD;
                                    2'b11: RF_RegSel = 4'hE;
                                endcase
                                RF_FunSel = 3'b010;
                                T = 8'h08;
                            end
                        6'h04:
                            begin
                                case(_ALUSystem.IR.IROut[9:8])
                                    2'b00: RF_OutASel = 3'b000;
                                    2'b01: RF_OutASel = 3'b001;
                                    2'b10: RF_OutASel = 3'b010;
                                    2'b11: RF_OutASel = 3'b011;
                                endcase
                                ALU_FunSel =  5'b10000;
                                MuxCSel = 1'b1;
                                Mem_CS = 1'b0;
                                Mem_WR = 1'b1;
                                ARF_OutDSel = 2'b11;
                                T = 8'h08;
                            end
                        6'h05:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            case(_ALUSystem.IR.IROut[8])
                                                1'b0:  // ARF
                                                    begin
                                                        MuxBSel = 2'b01;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: ARF_RegSel = 3'b011;
                                                            2'b01: ARF_RegSel = 3'b011;
                                                            2'b10: ARF_RegSel = 3'b110;
                                                            2'b11: ARF_RegSel = 3'b101;
                                                        endcase
                                                        ARF_FunSel = 3'b010;
                                                    end
                                                1'b1:  // RF
                                                    begin
                                                        MuxASel = 2'b01;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: RF_RegSel = 4'h7;
                                                            2'b01: RF_RegSel = 4'hB;
                                                            2'b10: RF_RegSel = 4'hD;
                                                            2'b11: RF_RegSel = 4'hE;
                                                        endcase
                                                        RF_FunSel = 3'b010;
                                                    end
                                            endcase
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                            ALU_FunSel = 5'b10000;
                                            case(_ALUSystem.IR.IROut[8])
                                                1'b0:  // ARF
                                                    begin
                                                        MuxBSel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: ARF_RegSel = 3'b011;
                                                            2'b01: ARF_RegSel = 3'b011;
                                                            2'b10: ARF_RegSel = 3'b110;
                                                            2'b11: ARF_RegSel = 3'b101;
                                                        endcase
                                                        ARF_FunSel = 3'b010;
                                                    end
                                                1'b1:  // RF
                                                    begin
                                                        MuxASel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: RF_RegSel = 4'h7;
                                                            2'b01: RF_RegSel = 4'hB;
                                                            2'b10: RF_RegSel = 4'hD;
                                                            2'b11: RF_RegSel = 4'hE;
                                                        endcase
                                                        RF_FunSel = 3'b010;
                                                    end
                                            endcase
                                        end
                                endcase
                                T = 8'h08;
                            end
                        6'h06:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            case(_ALUSystem.IR.IROut[8])
                                                1'b0:  // ARF
                                                    begin
                                                        MuxBSel = 2'b01;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: ARF_RegSel = 3'b011;
                                                            2'b01: ARF_RegSel = 3'b011;
                                                            2'b10: ARF_RegSel = 3'b110;
                                                            2'b11: ARF_RegSel = 3'b101;
                                                        endcase
                                                        ARF_FunSel = 3'b010;
                                                    end
                                                1'b1:  // RF
                                                    begin
                                                        MuxASel = 2'b01;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: RF_RegSel = 4'h7;
                                                            2'b01: RF_RegSel = 4'hB;
                                                            2'b10: RF_RegSel = 4'hD;
                                                            2'b11: RF_RegSel = 4'hE;
                                                        endcase
                                                        RF_FunSel = 3'b010;
                                                    end
                                            endcase
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                            ALU_FunSel = 5'b10000;
                                            case(_ALUSystem.IR.IROut[8])
                                                1'b0:  // ARF
                                                    begin
                                                        MuxBSel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: ARF_RegSel = 3'b011;
                                                            2'b01: ARF_RegSel = 3'b011;
                                                            2'b10: ARF_RegSel = 3'b110;
                                                            2'b11: ARF_RegSel = 3'b101;
                                                        endcase
                                                        ARF_FunSel = 3'b010;
                                                    end
                                                1'b1:  // RF
                                                    begin
                                                        MuxASel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: RF_RegSel = 4'h7;
                                                            2'b01: RF_RegSel = 4'hB;
                                                            2'b10: RF_RegSel = 4'hD;
                                                            2'b11: RF_RegSel = 4'hE;
                                                        endcase
                                                        RF_FunSel = 3'b010;
                                                    end
                                            endcase
                                        end
                                endcase
                                T = 8'h08;
                            end
                        6'h07:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                            ALU_FunSel = 5'b11011;
                                            case(_ALUSystem.IR.IROut[8])
                                                1'b0:  // ARF
                                                    begin
                                                        MuxBSel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: ARF_RegSel = 3'b011;
                                                            2'b01: ARF_RegSel = 3'b011;
                                                            2'b10: ARF_RegSel = 3'b110;
                                                            2'b11: ARF_RegSel = 3'b101;
                                                        endcase
                                                        ARF_FunSel = 3'b010;
                                                    end
                                                1'b1:  // RF
                                                    begin
                                                        MuxASel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: RF_RegSel = 4'h7;
                                                            2'b01: RF_RegSel = 4'hB;
                                                            2'b10: RF_RegSel = 4'hD;
                                                            2'b11: RF_RegSel = 4'hE;
                                                        endcase
                                                        RF_FunSel = 3'b010;
                                                    end
                                            endcase
                                        end
                                endcase
                                T = 8'h08;
                            end
                        6'h08:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                            ALU_FunSel = 5'b11100;
                                            case(_ALUSystem.IR.IROut[8])
                                                1'b0:  // ARF
                                                    begin
                                                        MuxBSel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: ARF_RegSel = 3'b011;
                                                            2'b01: ARF_RegSel = 3'b011;
                                                            2'b10: ARF_RegSel = 3'b110;
                                                            2'b11: ARF_RegSel = 3'b101;
                                                        endcase
                                                        ARF_FunSel = 3'b010;
                                                    end
                                                1'b1:  // RF
                                                    begin
                                                        MuxASel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: RF_RegSel = 4'h7;
                                                            2'b01: RF_RegSel = 4'hB;
                                                            2'b10: RF_RegSel = 4'hD;
                                                            2'b11: RF_RegSel = 4'hE;
                                                        endcase
                                                        RF_FunSel = 3'b010;
                                                    end
                                            endcase
                                        end
                                endcase
                                T = 8'h08;
                            end
                        6'h09:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                            ALU_FunSel = 5'b11101;
                                            case(_ALUSystem.IR.IROut[8])
                                                1'b0:  // ARF
                                                    begin
                                                        MuxBSel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: ARF_RegSel = 3'b011;
                                                            2'b01: ARF_RegSel = 3'b011;
                                                            2'b10: ARF_RegSel = 3'b110;
                                                            2'b11: ARF_RegSel = 3'b101;
                                                        endcase
                                                        ARF_FunSel = 3'b010;
                                                    end
                                                1'b1:  // RF
                                                    begin
                                                        MuxASel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: RF_RegSel = 4'h7;
                                                            2'b01: RF_RegSel = 4'hB;
                                                            2'b10: RF_RegSel = 4'hD;
                                                            2'b11: RF_RegSel = 4'hE;
                                                        endcase
                                                        RF_FunSel = 3'b010;
                                                    end
                                            endcase
                                        end
                                endcase
                                T = 8'h08;
                            end
                        6'h0A:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                            ALU_FunSel = 5'b11110;
                                            case(_ALUSystem.IR.IROut[8])
                                                1'b0:  // ARF
                                                    begin
                                                        MuxBSel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: ARF_RegSel = 3'b011;
                                                            2'b01: ARF_RegSel = 3'b011;
                                                            2'b10: ARF_RegSel = 3'b110;
                                                            2'b11: ARF_RegSel = 3'b101;
                                                        endcase
                                                        ARF_FunSel = 3'b010;
                                                    end
                                                1'b1:  // RF
                                                    begin
                                                        MuxASel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: RF_RegSel = 4'h7;
                                                            2'b01: RF_RegSel = 4'hB;
                                                            2'b10: RF_RegSel = 4'hD;
                                                            2'b11: RF_RegSel = 4'hE;
                                                        endcase
                                                        RF_FunSel = 3'b010;
                                                    end
                                            endcase
                                        end
                                endcase
                                T = 8'h08;
                            end
                        6'h0B:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                            ALU_FunSel = 5'b11111;
                                            case(_ALUSystem.IR.IROut[8])
                                                1'b0:  // ARF
                                                    begin
                                                        MuxBSel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: ARF_RegSel = 3'b011;
                                                            2'b01: ARF_RegSel = 3'b011;
                                                            2'b10: ARF_RegSel = 3'b110;
                                                            2'b11: ARF_RegSel = 3'b101;
                                                        endcase
                                                        ARF_FunSel = 3'b010;
                                                    end
                                                1'b1:  // RF
                                                    begin
                                                        MuxASel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: RF_RegSel = 4'h7;
                                                            2'b01: RF_RegSel = 4'hB;
                                                            2'b10: RF_RegSel = 4'hD;
                                                            2'b11: RF_RegSel = 4'hE;
                                                        endcase
                                                        RF_FunSel = 3'b010;
                                                    end
                                            endcase
                                        end
                                endcase
                                T = 8'h08;
                            end
                        6'h0C:
                            begin
                                ALU_FunSel = 5'b10111;
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                        end
                                endcase
                                T = 8'h08;
                            end
                        6'h0D:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                            RF_OutASel = 3'b100;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                        end
                                endcase
                                case(_ALUSystem.IR.IROut[2])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'hB;
                                            RF_FunSel = 3'b010;
                                            RF_OutBSel = 3'b101;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutBSel = 3'b000;
                                                2'b01: RF_OutBSel = 3'b001;
                                                2'b10: RF_OutBSel = 3'b010;
                                                2'b11: RF_OutBSel = 3'b011;
                                            endcase
                                        end
                                endcase
                                ALU_FunSel = 5'b11000;
                                T = 8'h08;
                            end
                        6'h0E:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                            ALU_FunSel = 5'b10010;
                                            case(_ALUSystem.IR.IROut[8])
                                                1'b0:  // ARF
                                                    begin
                                                        MuxBSel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: ARF_RegSel = 3'b011;
                                                            2'b01: ARF_RegSel = 3'b011;
                                                            2'b10: ARF_RegSel = 3'b110;
                                                            2'b11: ARF_RegSel = 3'b101;
                                                        endcase
                                                        ARF_FunSel = 3'b010;
                                                    end
                                                1'b1:  // RF
                                                    begin
                                                        MuxASel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: RF_RegSel = 4'h7;
                                                            2'b01: RF_RegSel = 4'hB;
                                                            2'b10: RF_RegSel = 4'hD;
                                                            2'b11: RF_RegSel = 4'hE;
                                                        endcase
                                                        RF_FunSel = 3'b010;
                                                    end
                                            endcase
                                        end
                                endcase
                                T = 8'h08;
                            end
                        6'h0F:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                            RF_OutASel = 3'b100;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                        end
                                endcase
                                case(_ALUSystem.IR.IROut[2])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'hB;
                                            RF_FunSel = 3'b010;
                                            RF_OutBSel = 3'b101;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutBSel = 3'b000;
                                                2'b01: RF_OutBSel = 3'b001;
                                                2'b10: RF_OutBSel = 3'b010;
                                                2'b11: RF_OutBSel = 3'b011;
                                            endcase
                                        end
                                endcase
                                ALU_FunSel = 5'b11001;
                                T = 8'h08;
                            end
                        6'h10:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                            RF_OutASel = 3'b100;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                        end
                                endcase
                                case(_ALUSystem.IR.IROut[2])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'hB;
                                            RF_FunSel = 3'b010;
                                            RF_OutBSel = 3'b101;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutBSel = 3'b000;
                                                2'b01: RF_OutBSel = 3'b001;
                                                2'b10: RF_OutBSel = 3'b010;
                                                2'b11: RF_OutBSel = 3'b011;
                                            endcase
                                        end
                                endcase
                                ALU_FunSel = 5'b11010;
                                T = 8'h08;
                            end
                        6'h11:
                            begin
                                ARF_OutCSel = 2'b00;
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            MuxBSel = 2'b01;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: ARF_RegSel = 3'b011;
                                                2'b01: ARF_RegSel = 3'b011;
                                                2'b10: ARF_RegSel = 3'b110;
                                                2'b11: ARF_RegSel = 3'b101;
                                            endcase
                                            ARF_FunSel = 3'b110;
                                        end
                                    1'b1:  // RF
                                        begin
                                            MuxASel = 2'b01;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: RF_RegSel = 4'h7;
                                                2'b01: RF_RegSel = 4'hB;
                                                2'b10: RF_RegSel = 4'hD;
                                                2'b11: RF_RegSel = 4'hE;
                                            endcase
                                            RF_FunSel = 3'b110;
                                        end
                                endcase
                                T = 8'h00;
                            end
                        6'h12:
                            begin
                                ARF_OutDSel = 2'b10;
                                Mem_CS = 1'b0;
                                Mem_WR = 1'b0;
                                MuxASel = 2'b10;
                                case(_ALUSystem.IR.IROut[9:8])
                                    2'b00: RF_RegSel = 4'h7;
                                    2'b01: RF_RegSel = 4'hB;
                                    2'b10: RF_RegSel = 4'hD;
                                    2'b11: RF_RegSel = 4'hE;
                                endcase
                                RF_FunSel = 3'b010;
                                T = 8'h08;
                            end
                        6'h13:
                            begin
                                case(_ALUSystem.IR.IROut[9:8])
                                    2'b00: RF_OutASel = 3'b000;
                                    2'b01: RF_OutASel = 3'b001;
                                    2'b10: RF_OutASel = 3'b010;
                                    2'b11: RF_OutASel = 3'b011;
                                endcase
                                ALU_FunSel = 5'b10000;
                                MuxCSel = 1'b0;
                                ARF_OutDSel = 2'b10;
                                Mem_CS = 1'b0;
                                Mem_WR = 1'b1;
                                T = 8'h08;
                            end
                        6'h14:
                            begin
                                ARF_OutCSel = 2'b00;
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            MuxBSel = 2'b01;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: ARF_RegSel = 3'b011;
                                                2'b01: ARF_RegSel = 3'b011;
                                                2'b10: ARF_RegSel = 3'b110;
                                                2'b11: ARF_RegSel = 3'b101;
                                            endcase
                                            ARF_FunSel = 3'b101;
                                        end
                                    1'b1:  // RF
                                        begin
                                            MuxASel = 2'b01;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: RF_RegSel = 4'h7;
                                                2'b01: RF_RegSel = 4'hB;
                                                2'b10: RF_RegSel = 4'hD;
                                                2'b11: RF_RegSel = 4'hE;
                                            endcase
                                            RF_FunSel = 3'b101;
                                        end
                                endcase
                                T = 8'h00;
                            end
                        6'h15:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                            RF_OutASel = 3'b100;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                        end
                                endcase
                                case(_ALUSystem.IR.IROut[2])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'hB;
                                            RF_FunSel = 3'b010;
                                            RF_OutBSel = 3'b101;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutBSel = 3'b000;
                                                2'b01: RF_OutBSel = 3'b001;
                                                2'b10: RF_OutBSel = 3'b010;
                                                2'b11: RF_OutBSel = 3'b011;
                                            endcase
                                        end
                                endcase
                                ALU_FunSel = 5'b10100;
                                T = 8'h08;
                            end
                        6'h16:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                            RF_OutASel = 3'b100;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                        end
                                endcase
                                case(_ALUSystem.IR.IROut[2])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'hB;
                                            RF_FunSel = 3'b010;
                                            RF_OutBSel = 3'b101;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutBSel = 3'b000;
                                                2'b01: RF_OutBSel = 3'b001;
                                                2'b10: RF_OutBSel = 3'b010;
                                                2'b11: RF_OutBSel = 3'b011;
                                            endcase
                                        end
                                endcase
                                ALU_FunSel = 5'b10101;
                                T = 8'h08;
                            end
                        6'h17:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                            RF_OutASel = 3'b100;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                        end
                                endcase
                                case(_ALUSystem.IR.IROut[2])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'hB;
                                            RF_FunSel = 3'b010;
                                            RF_OutBSel = 3'b101;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutBSel = 3'b000;
                                                2'b01: RF_OutBSel = 3'b001;
                                                2'b10: RF_OutBSel = 3'b010;
                                                2'b11: RF_OutBSel = 3'b011;
                                            endcase
                                        end
                                endcase
                                ALU_FunSel = 5'b10110;
                                T = 8'h08;
                            end
                        6'h18:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            case(_ALUSystem.IR.IROut[8])
                                                1'b0:  // ARF
                                                    begin
                                                        MuxBSel = 2'b01;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: ARF_RegSel = 3'b011;
                                                            2'b01: ARF_RegSel = 3'b011;
                                                            2'b10: ARF_RegSel = 3'b110;
                                                            2'b11: ARF_RegSel = 3'b101;
                                                        endcase
                                                        ARF_FunSel = 3'b010;
                                                    end
                                                1'b1:  // RF
                                                    begin
                                                        MuxASel = 2'b01;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: RF_RegSel = 4'h7;
                                                            2'b01: RF_RegSel = 4'hB;
                                                            2'b10: RF_RegSel = 4'hD;
                                                            2'b11: RF_RegSel = 4'hE;
                                                        endcase
                                                        RF_FunSel = 3'b010;
                                                    end
                                            endcase
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                            ALU_FunSel = 5'b10000;
                                            case(_ALUSystem.IR.IROut[8])
                                                1'b0:  // ARF
                                                    begin
                                                        MuxBSel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: ARF_RegSel = 3'b011;
                                                            2'b01: ARF_RegSel = 3'b011;
                                                            2'b10: ARF_RegSel = 3'b110;
                                                            2'b11: ARF_RegSel = 3'b101;
                                                        endcase
                                                        ARF_FunSel = 3'b010;
                                                    end
                                                1'b1:  // RF
                                                    begin
                                                        MuxASel = 2'b00;
                                                        case(_ALUSystem.IR.IROut[7:6])
                                                            2'b00: RF_RegSel = 4'h7;
                                                            2'b01: RF_RegSel = 4'hB;
                                                            2'b10: RF_RegSel = 4'hD;
                                                            2'b11: RF_RegSel = 4'hE;
                                                        endcase
                                                        RF_FunSel = 3'b010;
                                                    end
                                            endcase
                                        end
                                endcase
                                T = 8'h08;
                            end
                        6'h19:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                            RF_OutASel = 3'b100;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                        end
                                endcase
                                case(_ALUSystem.IR.IROut[2])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'hB;
                                            RF_FunSel = 3'b010;
                                            RF_OutBSel = 3'b101;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutBSel = 3'b000;
                                                2'b01: RF_OutBSel = 3'b001;
                                                2'b10: RF_OutBSel = 3'b010;
                                                2'b11: RF_OutBSel = 3'b011;
                                            endcase
                                        end
                                endcase
                                ALU_FunSel = 5'b10100;
                                T = 8'h08;
                            end
                        6'h1A:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                            RF_OutASel = 3'b100;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                        end
                                endcase
                                case(_ALUSystem.IR.IROut[2])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'hB;
                                            RF_FunSel = 3'b010;
                                            RF_OutBSel = 3'b101;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutBSel = 3'b000;
                                                2'b01: RF_OutBSel = 3'b001;
                                                2'b10: RF_OutBSel = 3'b010;
                                                2'b11: RF_OutBSel = 3'b011;
                                            endcase
                                        end
                                endcase
                                ALU_FunSel = 5'b10110;
                                T = 8'h08;
                            end
                        6'h1B:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                            RF_OutASel = 3'b100;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                        end
                                endcase
                                case(_ALUSystem.IR.IROut[2])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'hB;
                                            RF_FunSel = 3'b010;
                                            RF_OutBSel = 3'b101;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutBSel = 3'b000;
                                                2'b01: RF_OutBSel = 3'b001;
                                                2'b10: RF_OutBSel = 3'b010;
                                                2'b11: RF_OutBSel = 3'b011;
                                            endcase
                                        end
                                endcase
                                ALU_FunSel = 5'b10111;
                                T = 8'h08;
                            end
                        6'h1C:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                            RF_OutASel = 3'b100;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                        end
                                endcase
                                case(_ALUSystem.IR.IROut[2])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'hB;
                                            RF_FunSel = 3'b010;
                                            RF_OutBSel = 3'b101;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutBSel = 3'b000;
                                                2'b01: RF_OutBSel = 3'b001;
                                                2'b10: RF_OutBSel = 3'b010;
                                                2'b11: RF_OutBSel = 3'b011;
                                            endcase
                                        end
                                endcase
                                ALU_FunSel = 5'b11000;
                                T = 8'h08;
                            end
                        6'h1D:
                            begin
                                case(_ALUSystem.IR.IROut[5])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'h7;
                                            RF_FunSel = 3'b010;
                                            RF_OutASel = 3'b100;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutASel = 3'b000;
                                                2'b01: RF_OutASel = 3'b001;
                                                2'b10: RF_OutASel = 3'b010;
                                                2'b11: RF_OutASel = 3'b011;
                                            endcase
                                        end
                                endcase
                                case(_ALUSystem.IR.IROut[2])
                                    1'b0: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: ARF_OutCSel = 2'b00;
                                                2'b01: ARF_OutCSel = 2'b01;
                                                2'b10: ARF_OutCSel = 2'b11;
                                                2'b11: ARF_OutCSel = 2'b10;
                                            endcase
                                            MuxASel = 2'b01;
                                            RF_ScrSel = 4'hB;
                                            RF_FunSel = 3'b010;
                                            RF_OutBSel = 3'b101;
                                        end
                                    1'b1: 
                                        begin
                                            case(_ALUSystem.IR.IROut[4:3])
                                                2'b00: RF_OutBSel = 3'b000;
                                                2'b01: RF_OutBSel = 3'b001;
                                                2'b10: RF_OutBSel = 3'b010;
                                                2'b11: RF_OutBSel = 3'b011;
                                            endcase
                                        end
                                endcase
                                ALU_FunSel = 5'b11001;
                                T = 8'h08;
                            end
                        6'h1E:
                            begin
                                ARF_OutDSel = 2'b11;
                                ARF_OutCSel = 2'b00;
                                MuxASel = 2'b01;
                                RF_ScrSel = 4'h7;
                                RF_FunSel = 3'b010;
                                RF_OutASel = 3'b100;
                                ALU_FunSel = 5'b10000;
                                MuxCSel = 1'b0;
                                Mem_CS = 1'b0;
                                Mem_WR = 1'b1;
                                T = 8'h08;
                            end
                        6'h1F:
                            begin
                                ARF_OutDSel = 2'b11;
                                Mem_CS = 1'b0;
                                Mem_WR = 1'b0;
                                MuxBSel = 2'b10;
                                ARF_RegSel = 3'b011;
                                ARF_FunSel = 3'b010;
                                T = 8'h00;
                            end
                        6'h20:
                            begin
                                MuxASel = 2'b11;
                                case(_ALUSystem.IR.IROut[9:8])
                                    2'b00: RF_RegSel = 4'h7;
                                    2'b01: RF_RegSel = 4'hB;
                                    2'b10: RF_RegSel = 4'hD;
                                    2'b11: RF_RegSel = 4'hE;
                                endcase
                                RF_FunSel = 3'b010;
                            end
                        6'h21:
                            begin
                                MuxASel = 2'b11;
                                RF_ScrSel = 4'h7;
                                RF_FunSel = 3'b010;
                                RF_OutASel = 3'b100;
                                T = 8'h08;
                            end
                    endcase
                end
            8'h08:  // t4
                begin
                    case(_ALUSystem.IR.IROut[15:10])
                        6'h00:
                            begin
                                RF_OutASel = 3'b100;
                                ARF_OutCSel = 2'b00;
                                MuxASel = 2'b01;
                                RF_ScrSel = 4'hB;
                                T = 8'h10;
                            end
                        6'h01:
                            begin
                                RF_OutASel = 3'b100;
                                ARF_OutCSel = 2'b00;
                                MuxASel = 2'b01;
                                RF_ScrSel = 4'hB;
                                T = 8'h10;
                            end
                        6'h02:
                            begin
                                RF_OutASel = 3'b100;
                                ARF_OutCSel = 2'b00;
                                MuxASel = 2'b01;
                                RF_ScrSel = 4'hB;
                                T = 8'h10;
                            end
                        6'h03:
                            begin
                                ARF_RegSel = 3'b110;
                                ARF_FunSel = 3'b001;
                                T = 8'h00;
                            end
                        6'h04:
                            begin
                                ARF_RegSel = 3'b110; 
                                ARF_FunSel = 3'b000;
                                MuxCSel = 1'b0;
                                T = 8'h00;
                            end
                        6'h05:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            ARF_FunSel = 3'b001;
                                        end
                                    1'b1:  // RF
                                        begin
                                            RF_OutASel = 3'b100;
                                            RF_FunSel = 3'b001;
                                        end
                                endcase
                                T = 8'h10;
                            end
                        6'h06:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            ARF_FunSel = 3'b000;
                                        end
                                    1'b1:  // RF
                                        begin
                                            RF_OutASel = 3'b100;
                                            RF_FunSel = 3'b000;
                                        end
                                endcase
                                T = 8'h10;
                            end
                        6'h07:
                            begin
                                if(_ALUSystem.IR.IROut[5] == 0) begin
                                    RF_ScrSel = 4'hF;
                                    RF_OutASel = 3'b100;
                                    ALU_FunSel = 5'b11011;
                                    case(_ALUSystem.IR.IROut[8])
                                        1'b0:  // ARF
                                            begin
                                                MuxBSel = 2'b00;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: ARF_RegSel = 3'b011;
                                                    2'b01: ARF_RegSel = 3'b011;
                                                    2'b10: ARF_RegSel = 3'b110;
                                                    2'b11: ARF_RegSel = 3'b101;
                                                endcase
                                                ARF_FunSel = 3'b010;
                                            end
                                        1'b1:  // RF
                                            begin
                                                MuxASel = 2'b00;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: RF_RegSel = 4'h7;
                                                    2'b01: RF_RegSel = 4'hB;
                                                    2'b10: RF_RegSel = 4'hD;
                                                    2'b11: RF_RegSel = 4'hE;
                                                endcase
                                                RF_FunSel = 3'b010;
                                            end
                                    endcase
                                    T = 8'h10;
                                end
                                else begin
                                    ARF_RegSel = 3'b111;
                                    RF_RegSel = 4'hF;
                                    Clean;
                                    T = 8'h00;
                                end
                                RF_OutASel = 3'b100;
                            end
                        6'h08:
                            begin
                                if(_ALUSystem.IR.IROut[5] == 0) begin
                                    RF_ScrSel = 4'hF;
                                    RF_OutASel = 3'b100;
                                    ALU_FunSel = 5'b11100;
                                    case(_ALUSystem.IR.IROut[8])
                                        1'b0:  // ARF
                                            begin
                                                MuxBSel = 2'b00;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: ARF_RegSel = 3'b011;
                                                    2'b01: ARF_RegSel = 3'b011;
                                                    2'b10: ARF_RegSel = 3'b110;
                                                    2'b11: ARF_RegSel = 3'b101;
                                                endcase
                                                ARF_FunSel = 3'b010;
                                            end
                                        1'b1:  // RF
                                            begin
                                                MuxASel = 2'b00;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: RF_RegSel = 4'h7;
                                                    2'b01: RF_RegSel = 4'hB;
                                                    2'b10: RF_RegSel = 4'hD;
                                                    2'b11: RF_RegSel = 4'hE;
                                                endcase
                                                RF_FunSel = 3'b010;
                                            end
                                    endcase
                                    T = 8'h10;
                                end
                                else begin
                                    ARF_RegSel = 3'b111;
                                    RF_RegSel = 4'hF;
                                    Clean;
                                    T = 8'h00;
                                end
                                RF_OutASel = 3'b100;
                            end
                        6'h09:
                            begin
                                if(_ALUSystem.IR.IROut[5] == 0) begin
                                    RF_ScrSel = 4'hF;
                                    RF_OutASel = 3'b100;
                                    ALU_FunSel = 5'b11101;
                                    case(_ALUSystem.IR.IROut[8])
                                        1'b0:  // ARF
                                            begin
                                                MuxBSel = 2'b00;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: ARF_RegSel = 3'b011;
                                                    2'b01: ARF_RegSel = 3'b011;
                                                    2'b10: ARF_RegSel = 3'b110;
                                                    2'b11: ARF_RegSel = 3'b101;
                                                endcase
                                                ARF_FunSel = 3'b010;
                                            end
                                        1'b1:  // RF
                                            begin
                                                MuxASel = 2'b00;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: RF_RegSel = 4'h7;
                                                    2'b01: RF_RegSel = 4'hB;
                                                    2'b10: RF_RegSel = 4'hD;
                                                    2'b11: RF_RegSel = 4'hE;
                                                endcase
                                                RF_FunSel = 3'b010;
                                            end
                                    endcase
                                    T = 8'h10;
                                end
                                else begin
                                    ARF_RegSel = 3'b111;
                                    RF_RegSel = 4'hF;
                                    Clean;
                                    T = 8'h00;
                                end
                                RF_OutASel = 3'b100;
                            end
                        6'h0A:
                            begin
                                if(_ALUSystem.IR.IROut[5] == 0) begin
                                    RF_ScrSel = 4'hF;
                                    RF_OutASel = 3'b100;
                                    ALU_FunSel = 5'b11110;
                                    case(_ALUSystem.IR.IROut[8])
                                        1'b0:  // ARF
                                            begin
                                                MuxBSel = 2'b00;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: ARF_RegSel = 3'b011;
                                                    2'b01: ARF_RegSel = 3'b011;
                                                    2'b10: ARF_RegSel = 3'b110;
                                                    2'b11: ARF_RegSel = 3'b101;
                                                endcase
                                                ARF_FunSel = 3'b010;
                                            end
                                        1'b1:  // RF
                                            begin
                                                MuxASel = 2'b00;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: RF_RegSel = 4'h7;
                                                    2'b01: RF_RegSel = 4'hB;
                                                    2'b10: RF_RegSel = 4'hD;
                                                    2'b11: RF_RegSel = 4'hE;
                                                endcase
                                                RF_FunSel = 3'b010;
                                            end
                                    endcase
                                    T = 8'h10;
                                end
                                else begin
                                    ARF_RegSel = 3'b111;
                                    RF_RegSel = 4'hF;
                                    Clean;
                                    T = 8'h00;
                                end
                                RF_OutASel = 3'b100;
                            end
                        6'h0B:
                            begin
                                if(_ALUSystem.IR.IROut[5] == 0) begin
                                    RF_ScrSel = 4'hF;
                                    RF_OutASel = 3'b100;
                                    ALU_FunSel = 5'b11111;
                                    case(_ALUSystem.IR.IROut[8])
                                        1'b0:  // ARF
                                            begin
                                                MuxBSel = 2'b00;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: ARF_RegSel = 3'b011;
                                                    2'b01: ARF_RegSel = 3'b011;
                                                    2'b10: ARF_RegSel = 3'b110;
                                                    2'b11: ARF_RegSel = 3'b101;
                                                endcase
                                                ARF_FunSel = 3'b010;
                                            end
                                        1'b1:  // RF
                                            begin
                                                MuxASel = 2'b00;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: RF_RegSel = 4'h7;
                                                    2'b01: RF_RegSel = 4'hB;
                                                    2'b10: RF_RegSel = 4'hD;
                                                    2'b11: RF_RegSel = 4'hE;
                                                endcase
                                                RF_FunSel = 3'b010;
                                            end
                                    endcase
                                    T = 8'h10;
                                end
                                else begin
                                    ARF_RegSel = 3'b111;
                                    RF_RegSel = 4'hF;
                                    Clean;
                                    T = 8'h00;
                                end
                                RF_OutASel = 3'b100;
                            end
                        6'h0C:
                           begin
                                if (_ALUSystem.IR.IROut[5] == 0) begin
                                    RF_OutASel = 3'b100;
                                    case(_ALUSystem.IR.IROut[2])
                                        1'b0: 
                                            begin
                                                case(_ALUSystem.IR.IROut[4:3])
                                                    2'b00: ARF_OutCSel = 2'b00;
                                                    2'b01: ARF_OutCSel = 2'b01;
                                                    2'b10: ARF_OutCSel = 2'b11;
                                                    2'b11: ARF_OutCSel = 2'b10;
                                                endcase
                                                MuxASel = 2'b01;
                                                RF_FunSel = 3'b010;
                                            end
                                        1'b1: 
                                            begin
                                                case(_ALUSystem.IR.IROut[4:3])
                                                    2'b00: RF_OutBSel = 3'b000;
                                                    2'b01: RF_OutBSel = 3'b001;
                                                    2'b10: RF_OutBSel = 3'b010;
                                                    2'b11: RF_OutBSel = 3'b011;
                                                endcase
                                            end
                                    endcase
                                end
                                else 
                                    begin
                                        case(_ALUSystem.IR.IROut[2])
                                            1'b0: 
                                                begin
                                                    case(_ALUSystem.IR.IROut[4:3])
                                                        2'b00: ARF_OutCSel = 2'b00;
                                                        2'b01: ARF_OutCSel = 2'b01;
                                                        2'b10: ARF_OutCSel = 2'b11;
                                                        2'b11: ARF_OutCSel = 2'b10;
                                                    endcase
                                                    MuxASel = 2'b01;
                                                    RF_FunSel = 3'b010;
                                                    RF_ScrSel = 4'hB;
                                                end
                                            1'b1: 
                                                begin
                                                    case(_ALUSystem.IR.IROut[4:3])
                                                        2'b00: RF_OutBSel = 3'b000;
                                                        2'b01: RF_OutBSel = 3'b001;
                                                        2'b10: RF_OutBSel = 3'b010;
                                                        2'b11: RF_OutBSel = 3'b011;
                                                    endcase
                                                end
                                        endcase
                                    end
                                T = 8'h10;
                            end
                        6'h0D:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            MuxBSel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: ARF_RegSel = 3'b011;
                                                2'b01: ARF_RegSel = 3'b011;
                                                2'b10: ARF_RegSel = 3'b110;
                                                2'b11: ARF_RegSel = 3'b101;
                                            endcase
                                            ARF_FunSel = 3'b010;
                                        end
                                    1'b1:  // RF
                                        begin
                                            MuxASel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: RF_RegSel = 4'h7;
                                                2'b01: RF_RegSel = 4'hB;
                                                2'b10: RF_RegSel = 4'hD;
                                                2'b11: RF_RegSel = 4'hE;
                                            endcase
                                            RF_FunSel = 3'b010;
                                        end
                                endcase
                                T = 8'h00;
                            end
                        6'h0E:
                            begin
                                if(_ALUSystem.IR.IROut[5] == 0) begin
                                    RF_OutASel = 3'b100;
                                    RF_ScrSel = 4'hF;
                                    ALU_FunSel = 5'b10010;
                                    case(_ALUSystem.IR.IROut[8])
                                        1'b0:  // ARF
                                            begin
                                                MuxBSel = 2'b00;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: ARF_RegSel = 3'b011;
                                                    2'b01: ARF_RegSel = 3'b011;
                                                    2'b10: ARF_RegSel = 3'b110;
                                                    2'b11: ARF_RegSel = 3'b101;
                                                endcase
                                                ARF_FunSel = 3'b010;
                                            end
                                        1'b1:  // RF
                                            begin
                                                MuxASel = 2'b00;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: RF_RegSel = 4'h7;
                                                    2'b01: RF_RegSel = 4'hB;
                                                    2'b10: RF_RegSel = 4'hD;
                                                    2'b11: RF_RegSel = 4'hE;
                                                endcase
                                                RF_FunSel = 3'b010;
                                            end
                                    endcase
                                    T = 8'h10;
                                end
                                else begin
                                    ALU_FunSel = 5'b10000;
                                    ARF_RegSel = 3'b111;
                                    RF_RegSel = 4'hF;
                                    Clean;
                                    T = 8'h00;
                                end
                                RF_OutASel = 3'b100;
                            end
                        6'h0F:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            MuxBSel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: ARF_RegSel = 3'b011;
                                                2'b01: ARF_RegSel = 3'b011;
                                                2'b10: ARF_RegSel = 3'b110;
                                                2'b11: ARF_RegSel = 3'b101;
                                            endcase
                                            ARF_FunSel = 3'b010;
                                        end
                                    1'b1:  // RF
                                        begin
                                            MuxASel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: RF_RegSel = 4'h7;
                                                2'b01: RF_RegSel = 4'hB;
                                                2'b10: RF_RegSel = 4'hD;
                                                2'b11: RF_RegSel = 4'hE;
                                            endcase
                                            RF_FunSel = 3'b010;
                                        end
                                endcase
                                T = 8'h00;
                            end
                        6'h10:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            MuxBSel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: ARF_RegSel = 3'b011;
                                                2'b01: ARF_RegSel = 3'b011;
                                                2'b10: ARF_RegSel = 3'b110;
                                                2'b11: ARF_RegSel = 3'b101;
                                            endcase
                                            ARF_FunSel = 3'b010;
                                        end
                                    1'b1:  // RF
                                        begin
                                            MuxASel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: RF_RegSel = 4'h7;
                                                2'b01: RF_RegSel = 4'hB;
                                                2'b10: RF_RegSel = 4'hD;
                                                2'b11: RF_RegSel = 4'hE;
                                            endcase
                                            RF_FunSel = 3'b010;
                                        end
                                endcase
                                T = 8'h00;
                            end
                        6'h12:
                            begin
                                ARF_RegSel = 3'b111;
                                RF_RegSel = 4'hF;
                                Clean;
                                T = 8'h00;
                            end
                        6'h13:
                            begin
                                ARF_RegSel = 3'b101;
                                ARF_FunSel = 3'b001;
                                MuxCSel = 1'b1;
                                T = 8'h10;
                            end
                        6'h15:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            MuxBSel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: ARF_RegSel = 3'b011;
                                                2'b01: ARF_RegSel = 3'b011;
                                                2'b10: ARF_RegSel = 3'b110;
                                                2'b11: ARF_RegSel = 3'b101;
                                            endcase
                                            ARF_FunSel = 3'b010;
                                        end
                                    1'b1:  // RF
                                        begin
                                            MuxASel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: RF_RegSel = 4'h7;
                                                2'b01: RF_RegSel = 4'hB;
                                                2'b10: RF_RegSel = 4'hD;
                                                2'b11: RF_RegSel = 4'hE;
                                            endcase
                                            RF_FunSel = 3'b010;
                                        end
                                endcase
                                T = 8'h00;
                            end
                        6'h16:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            MuxBSel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: ARF_RegSel = 3'b011;
                                                2'b01: ARF_RegSel = 3'b011;
                                                2'b10: ARF_RegSel = 3'b110;
                                                2'b11: ARF_RegSel = 3'b101;
                                            endcase
                                            ARF_FunSel = 3'b010;
                                        end
                                    1'b1:  // RF
                                        begin
                                            MuxASel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: RF_RegSel = 4'h7;
                                                2'b01: RF_RegSel = 4'hB;
                                                2'b10: RF_RegSel = 4'hD;
                                                2'b11: RF_RegSel = 4'hE;
                                            endcase
                                            RF_FunSel = 3'b010;
                                        end
                                endcase
                                T = 8'h00;
                            end
                        6'h17:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            MuxBSel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: ARF_RegSel = 3'b011;
                                                2'b01: ARF_RegSel = 3'b011;
                                                2'b10: ARF_RegSel = 3'b110;
                                                2'b11: ARF_RegSel = 3'b101;
                                            endcase
                                            ARF_FunSel = 3'b010;
                                        end
                                    1'b1:  // RF
                                        begin
                                            MuxASel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: RF_RegSel = 4'h7;
                                                2'b01: RF_RegSel = 4'hB;
                                                2'b10: RF_RegSel = 4'hD;
                                                2'b11: RF_RegSel = 4'hE;
                                            endcase
                                            RF_FunSel = 3'b010;
                                        end
                                endcase
                                T = 8'h00;
                            end
                        6'h18:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            ARF_FunSel = 3'b010;
                                        end
                                    1'b1:  // RF
                                        begin
                                            RF_OutASel = 3'b100;
                                            RF_FunSel = 3'b010;
                                        end
                                endcase
                                T = 8'h10;
                            end
                        6'h19:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            MuxBSel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: ARF_RegSel = 3'b011;
                                                2'b01: ARF_RegSel = 3'b011;
                                                2'b10: ARF_RegSel = 3'b110;
                                                2'b11: ARF_RegSel = 3'b101;
                                            endcase
                                            ARF_FunSel = 3'b010;
                                        end
                                    1'b1:  // RF
                                        begin
                                            MuxASel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: RF_RegSel = 4'h7;
                                                2'b01: RF_RegSel = 4'hB;
                                                2'b10: RF_RegSel = 4'hD;
                                                2'b11: RF_RegSel = 4'hE;
                                            endcase
                                            RF_FunSel = 3'b010;
                                        end
                                endcase
                                T = 8'h00;
                            end
                        6'h1A:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            MuxBSel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: ARF_RegSel = 3'b011;
                                                2'b01: ARF_RegSel = 3'b011;
                                                2'b10: ARF_RegSel = 3'b110;
                                                2'b11: ARF_RegSel = 3'b101;
                                            endcase
                                            ARF_FunSel = 3'b010;
                                        end
                                    1'b1:  // RF
                                        begin
                                            MuxASel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: RF_RegSel = 4'h7;
                                                2'b01: RF_RegSel = 4'hB;
                                                2'b10: RF_RegSel = 4'hD;
                                                2'b11: RF_RegSel = 4'hE;
                                            endcase
                                            RF_FunSel = 3'b010;
                                        end
                                endcase
                                T = 8'h00;
                            end
                        6'h1B:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            MuxBSel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: ARF_RegSel = 3'b011;
                                                2'b01: ARF_RegSel = 3'b011;
                                                2'b10: ARF_RegSel = 3'b110;
                                                2'b11: ARF_RegSel = 3'b101;
                                            endcase
                                            ARF_FunSel = 3'b010;
                                        end
                                    1'b1:  // RF
                                        begin
                                            MuxASel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: RF_RegSel = 4'h7;
                                                2'b01: RF_RegSel = 4'hB;
                                                2'b10: RF_RegSel = 4'hD;
                                                2'b11: RF_RegSel = 4'hE;
                                            endcase
                                            RF_FunSel = 3'b010;
                                        end
                                endcase
                                T = 8'h00;
                            end
                        6'h1C:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            MuxBSel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: ARF_RegSel = 3'b011;
                                                2'b01: ARF_RegSel = 3'b011;
                                                2'b10: ARF_RegSel = 3'b110;
                                                2'b11: ARF_RegSel = 3'b101;
                                            endcase
                                            ARF_FunSel = 3'b010;
                                        end
                                    1'b1:  // RF
                                        begin
                                            MuxASel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: RF_RegSel = 4'h7;
                                                2'b01: RF_RegSel = 4'hB;
                                                2'b10: RF_RegSel = 4'hD;
                                                2'b11: RF_RegSel = 4'hE;
                                            endcase
                                            RF_FunSel = 3'b010;
                                        end
                                endcase
                                T = 8'h00;
                            end
                        6'h1D:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            MuxBSel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: ARF_RegSel = 3'b011;
                                                2'b01: ARF_RegSel = 3'b011;
                                                2'b10: ARF_RegSel = 3'b110;
                                                2'b11: ARF_RegSel = 3'b101;
                                            endcase
                                            ARF_FunSel = 3'b010;
                                        end
                                    1'b1:  // RF
                                        begin
                                            MuxASel = 2'b00;
                                            case(_ALUSystem.IR.IROut[7:6])
                                                2'b00: RF_RegSel = 4'h7;
                                                2'b01: RF_RegSel = 4'hB;
                                                2'b10: RF_RegSel = 4'hD;
                                                2'b11: RF_RegSel = 4'hE;
                                            endcase
                                            RF_FunSel = 3'b010;
                                        end
                                endcase
                                T = 8'h00;
                            end
                        6'h1E:
                            begin
                                ARF_RegSel = 3'b110;
                                ARF_FunSel = 3'b001;
                                ARF_OutDSel = 2'b11;
                                MuxCSel = 1'b1;
                                T = 8'h10;
                            end
                        6'h21:
                            begin
                                ARF_OutCSel = 2'b00;
                                MuxASel = 2'b01;
                                RF_ScrSel = 4'hB;
                                RF_FunSel = 3'b010;
                                RF_OutBSel = 3'b101;
                                ALU_FunSel = 5'b10100;
                                MuxBSel = 2'b00;
                                ARF_RegSel = 3'b101;
                                ARF_FunSel = 3'b010;
                                T = 8'h10;
                            end
                    endcase
                end
            8'h10: // t5
                begin
                    case(_ALUSystem.IR.IROut[15:10])
                        6'h00:
                            begin
                                RF_ScrSel = 4'hF;
                                RF_OutBSel = 3'b101;
                                ALU_FunSel = 5'b10100;
                                MuxBSel = 2'b00;
                                ARF_RegSel = 3'b011;
                                ARF_FunSel = 3'b010;
                                T = 8'h20;
                            end
                        6'h01:
                            begin
                                RF_ScrSel = 4'hF;
                                RF_OutBSel = 3'b101;
                                ALU_FunSel = 5'b10100;
                                MuxBSel = 2'b00;
                                ARF_RegSel = 3'b011;
                                ARF_FunSel = 3'b010;
                                T = 8'h20;
                            end
                        6'h02:
                            begin
                                RF_ScrSel = 4'hF;
                                RF_OutBSel = 3'b101;
                                ALU_FunSel = 5'b10100;
                                MuxBSel = 2'b00;
                                ARF_RegSel = 3'b011;
                                ARF_FunSel = 3'b010;
                                T = 8'h20;
                            end
                        6'h05:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            ARF_FunSel = 3'b010;
                                            ARF_RegSel = 3'b111;
                                        end
                                    1'b1:  // RF
                                        begin
                                            RF_FunSel = 3'b010;
                                            RF_RegSel = 4'hF;
                                        end
                                endcase
                                Clean;
                                T = 8'h00;
                            end
                        6'h06:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            ARF_FunSel = 3'b010;
                                            ARF_RegSel = 3'b111;
                                        end
                                    1'b1:  // RF
                                        begin
                                            RF_FunSel = 3'b010;
                                            RF_RegSel = 4'hF;
                                        end
                                endcase
                                Clean;
                                T = 8'h00;
                            end
                        6'h07:
                            begin
                                ARF_RegSel = 3'b111;
                                RF_RegSel = 4'hF;
                                Clean;
                                T = 8'h00;
                            end
                        6'h08:
                            begin
                                ARF_RegSel = 3'b111;
                                RF_RegSel = 4'hF;
                                Clean;
                                T = 8'h00;
                            end
                        6'h09:
                            begin
                                ARF_RegSel = 3'b111;
                                RF_RegSel = 4'hF;
                                Clean;
                                T = 8'h00;
                            end
                        6'h0A:
                            begin
                                ARF_RegSel = 3'b111;
                                RF_RegSel = 4'hF;
                                Clean;
                                T = 8'h00;
                            end
                        6'h0B:
                            begin
                                ARF_RegSel = 3'b111;
                                RF_RegSel = 4'hF;
                                Clean;
                                T = 8'h00;
                            end
                        6'h0C:
                           begin
                                if ((_ALUSystem.IR.IROut[5] == 0) && (_ALUSystem.IR.IROut[2] == 0)) begin
                                    RF_ScrSel = 4'hB;
                                end
                                else begin
                                    if ((_ALUSystem.IR.IROut[2] == 0)) begin
                                        RF_OutBSel = 3'b101;
                                    end
                                    ALU_FunSel = 5'b10111;
                                    case(_ALUSystem.IR.IROut[8])
                                        1'b0: //ARF
                                            begin
                                                MuxBSel = 2'b00;
                                                ARF_FunSel = 3'b010;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: ARF_RegSel = 3'b011;
                                                    2'b01: ARF_RegSel = 3'b011;
                                                    2'b10: ARF_RegSel = 3'b110;
                                                    2'b11: ARF_RegSel = 3'b101;
                                                endcase
                                            end
                                        1'b1: //RF
                                            begin
                                                MuxASel = 2'b00;
                                                RF_FunSel = 3'b010;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: RF_RegSel = 4'h7;
                                                    2'b01: RF_RegSel = 4'hB;
                                                    2'b10: RF_RegSel = 4'hD;
                                                    2'b11: RF_RegSel = 4'hE;
                                                endcase
                                            end
                                    endcase
                                end
                                T = 8'h20;
                            end
                        6'h0E:
                            begin
                                ALU_FunSel = 5'b10000;
                                ARF_RegSel = 3'b111;
                                RF_RegSel = 4'hF;
                                Clean;
                                T = 8'h00;
                            end
                        6'h13:
                            begin
                                ARF_RegSel = 3'b111;
                                RF_RegSel = 4'hF;
                                Clean;
                                T = 8'h00;
                            end
                        6'h18:
                            begin
                                case(_ALUSystem.IR.IROut[8])
                                    1'b0:  // ARF
                                        begin
                                            ARF_FunSel = 3'b010;
                                            ARF_RegSel = 3'b111;
                                        end
                                    1'b1:  // RF
                                        begin
                                            RF_FunSel = 3'b010;
                                            RF_RegSel = 4'hF;
                                        end
                                endcase
                                Clean;
                                T = 8'h00;
                            end
                        6'h1E:
                            begin
                                Mem_CS = 1'b1;
                                case(_ALUSystem.IR.IROut[9:8])
                                    2'b00: RF_OutASel = 3'b000;
                                    2'b01: RF_OutASel = 3'b001;
                                    2'b10: RF_OutASel = 3'b010;
                                    2'b11: RF_OutASel = 3'b011;
                                endcase
                                ALU_FunSel = 5'b10000;
                                MuxBSel = 2'b00;
                                ARF_RegSel = 3'b011;
                                ARF_FunSel = 3'b010;
                                T = 8'h00;
                            end
                        6'h21:
                            begin
                                case(_ALUSystem.IR.IROut[9:8])
                                    2'b00: RF_OutASel = 3'b000;
                                    2'b01: RF_OutASel = 3'b001;
                                    2'b10: RF_OutASel = 3'b010;
                                    2'b11: RF_OutASel = 3'b011;
                                endcase
                                ALU_FunSel = 5'b10000;
                                MuxCSel = 1'b0;
                                ARF_OutDSel = 2'b10;
                                Mem_CS = 1'b0;
                                Mem_WR = 1'b1;
                                T = 8'h20;
                            end
                    endcase
                end
            8'h20: // t6
                begin
                    case(_ALUSystem.IR.IROut[15:10])
                        6'h00: 
                            begin
                                ARF_RegSel = 3'b111;
                                Clean;
                                T = 8'h00;
                            end
                        6'h01: 
                            begin
                                ARF_RegSel = 3'b111;
                                Clean;
                                T = 8'h00;
                            end
                        6'h02: 
                            begin
                                ARF_RegSel = 3'b111;
                                Clean;
                                T = 8'h00;
                            end
                        6'h0C:
                            begin
                                if ((_ALUSystem.IR.IROut[5] == 0) && (_ALUSystem.IR.IROut[2] == 0)) begin
                                    RF_OutBSel = 3'b101;
                                    ALU_FunSel = 5'b10111;
                                    case(_ALUSystem.IR.IROut[8])
                                        1'b0: //ARF
                                            begin
                                                MuxBSel = 2'b00;
                                                ARF_FunSel = 3'b010;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: ARF_RegSel = 3'b011;
                                                    2'b01: ARF_RegSel = 3'b011;
                                                    2'b10: ARF_RegSel = 3'b110;
                                                    2'b11: ARF_RegSel = 3'b101;
                                                endcase
                                            end
                                        1'b1: //RF
                                            begin
                                                MuxASel = 2'b00;
                                                RF_FunSel = 3'b010;
                                                case(_ALUSystem.IR.IROut[7:6])
                                                    2'b00: RF_RegSel = 4'h7;
                                                    2'b01: RF_RegSel = 4'hB;
                                                    2'b10: RF_RegSel = 4'hD;
                                                    2'b11: RF_RegSel = 4'hE;
                                                endcase
                                            end
                                    endcase
                                    T = 8'h40;
                                end
                                else begin
                                    ARF_RegSel = 3'b111;
                                    RF_RegSel = 4'hF;
                                    Clean;
                                    T = 8'h00;
                                end
                            end
                        6'h21:
                            begin
                                ARF_RegSel = 3'b101;
                                ARF_FunSel = 3'b001;
                                ARF_OutDSel = 2'b10;
                                MuxCSel = 1'b1;
                                T = 8'h00;
                            end
                    endcase
                end
            8'h40: // t7
                begin
                    case(_ALUSystem.IR.IROut[15:10])
                        6'h0C:
                            begin
                                ARF_RegSel = 3'b111;
                                RF_RegSel = 4'hF;
                                Clean;
                                T = 8'h00;
                            end
                    endcase
                end
        endcase
    end
endmodule