`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ITU Computer Engineering Department
// Engineer: Emre Bozkurt | Harun Yahya Demirpençe
// Project Name: BLG222E Project 1 
//////////////////////////////////////////////////////////////////////////////////

module AddressRegisterFile(
    I, OutCSel, OutDSel, FunSel, RegSel, Clock, OutC, OutD
);
    input wire  [15:0] I;
    input wire  [1:0]  OutCSel, OutDSel;
    input wire  [2:0]  FunSel, RegSel;
    input wire         Clock;
    output reg  [15:0] OutC, OutD;
           reg  [2:0]  ER;
           wire [15:0] Q1, Q2, Q3; 

    Register PC(.I(I), .E(~RegSel[2]), .FunSel(FunSel), .Clock(Clock), .Q(Q1));
    Register AR(.I(I), .E(~RegSel[1]), .FunSel(FunSel), .Clock(Clock), .Q(Q2));
    Register SP(.I(I), .E(~RegSel[0]), .FunSel(FunSel), .Clock(Clock), .Q(Q3));
    
    always @* begin
        case(OutCSel)
            2'b00: OutC = Q1;
            2'b01: OutC = Q1;
            2'b10: OutC = Q2;
            2'b11: OutC = Q3;
        endcase
        case(OutDSel)
            2'b00: OutD = Q1;
            2'b01: OutD = Q1;
            2'b10: OutD = Q2;
            2'b11: OutD = Q3;
        endcase
    end

endmodule