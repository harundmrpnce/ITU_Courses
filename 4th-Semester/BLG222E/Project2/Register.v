`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ITU Computer Engineering Department
// Engineer: Emre Bozkurt | Harun Yahya Demirpençe
// Project Name: BLG222E Project 1
//////////////////////////////////////////////////////////////////////////////////

module Register(I, E, FunSel, Clock, Q);
    input  wire [15:0]  I;
    input  wire [2:0]   FunSel;
    input  wire         Clock, E;
    output reg  [15:0]  Q;
    
    always @(posedge Clock) begin
        if(E) begin
            case(FunSel)
                3'b000: Q <= Q-1;
                3'b001: Q <= Q+1;
                3'b010: Q <= I;
                3'b011: Q <= 0;
                3'b100: Q <= {8'h00,   I[7:0]};
                3'b101: Q <= {Q[15:8], I[7:0]};
                3'b110: Q <= {I[7:0],  Q[7:0]};
                3'b111: 
                    if (I[7] == 1) Q <= {8'h11,   I[7:0]};
                    else Q <= {8'h00,   I[7:0]};
            endcase
        end
        else Q <= Q;
    end
endmodule