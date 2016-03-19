class ChannelMap {
public:
  ChannelMap(string MapFile);

  void AddUnknownChannel(int Module, int Channel);
  bool Identify(int Module, int Channel, string& Det_Type, int& Det_ID, int& Det_Ch);
  void WriteUnknownChannels(string File);

private:
  int TotalChannels;
  // Useful random number.
  TRandom3* rand;                               

  int *Module, *Chan;
  string* Det_Type;
  int *Det_ID, *Det_Ch;

  // Arrays for unknown ASICs and CAEN channels.
  int *UK_Module, *UK_Channel, *UK_Freq;
  int MaxUnknownChannels, TotUnknown;
};
