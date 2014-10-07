Var
  MinS,MinV:array[1..20] of integer;
  n,m,AnsS:integer;

Function Min(a,b:integer):integer;
begin
  if a>b then exit(b) else exit(a);
end;

Procedure DFS(SumV,SumS,Level,R,H:integer);
var
  i,j,MaxH:integer;
begin
  if Level=0 then
  begin
    if (SumV=n) and (SumS<AnsS) then AnsS:=SumS;
    exit;
  end;

  if (SumV+MinV[Level]>n)              //剪枝1：已搜索的体积+剩余层的体积的最小值不能大于目标值
  or (SumS+MinS[Level]>AnsS)           //剪枝2：已搜索的面积+剩余层的面积的最小值不能大于现有答案
  or (SumS+2*((n-SumV) div R)>=AnsS)   //剪枝3：总体积n，当前层半径R，SumS只是外面积，加上下顶面2*pi*R
  then exit;                           //       （h=1所以2*pi*R*h=2*(n-SumV)/R）构成表面积要小于现有答案

  for i:=R-1 downto Level do           //从大到小枚举下一层可用半径
  begin
    if Level=m then SumS:=i*i;         //当前是底层的话先把上表面加上去
    //剪枝4：假设将所有体积分配给下一层，得到一个高度Hn，因为可能有更下一层
    //       所以下一层的高度，最大不超过Min(Hn,H-1)
    MaxH:=Min(H-1,((n-MinV[Level-1]-SumV) div (i*i)));
    for j:=MaxH downto Level do        //从大到小枚举下一层可用高度
      DFS(SumV+i*i*j,SumS+2*i*j,Level-1,i,j);
  end;
end;

Procedure CalcMin;
var
  i:integer;
begin
  MinV[1]:=1;
  MinS[1]:=2;
  for i:=2 to m do
  begin
    MinV[i]:=MinV[i-1]+(i*i*i);  //h=i,r=i是取最小的体积
    MinS[i]:=MinS[i-1]+(2*i*i);
  end;
end;

Begin
  readln(n);
  readln(m);
  CalcMin;
  AnsS:=maxint;
  DFS(0,0,m,n+1,n+1);
  if AnsS=maxint then AnsS:=0;
  writeln(AnsS);
End.
