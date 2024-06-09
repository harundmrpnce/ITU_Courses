`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ITU Computer Engineering Department
// Engineer: Emre Bozkurt | Harun Yahya Demirpençe
// Project Name: BLG222E Project 1
//////////////////////////////////////////////////////////////////////////////////

module InstructionRegister(
        I, Write, LH, Clock, IROut
    );
    input  wire [7:0]  I;
    input  wire        Write, Clock, LH;
    output reg  [15:0] IROut;

    always @(posedge Clock) begin
        if(Write) begin
            case(LH)
                1'b0: IROut <= {IROut[15:8], I};
                1'b1: IROut <= {I, IROut[7:0]};
            endcase
        end
        else IROut <= IROut;
    end
endmodule
