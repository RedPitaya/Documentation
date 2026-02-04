
struct ADCChannel {
    uint32_t samples = 0;
    uint8_t bitsBySample = 0;
    uint64_t fpgaLost = 0;
    bool attenuator_1_20 = 0;
    uint32_t baseRate = 0;
    uint8_t adcBaseBits = 0;
    uint64_t packId = 0;
    std::vector<int16_t> raw;
};

struct ADCPack {
    std::string host;
    ADCChannel channel1;
    ADCChannel channel2;
    ADCChannel channel3;
    ADCChannel channel4;
};

class ADCStreamClient;
class DACStreamClient;

class ADCCallback {
   public:
    virtual ~ADCCallback() {}
    virtual void recievePack(ADCStreamClient*, ADCPack& pack) {}
    virtual void connected(ADCStreamClient*, std::string) {}
    virtual void disconnected(ADCStreamClient*, std::string) {}
    virtual void error(ADCStreamClient*, std::string, int) {}
    virtual void stopped(ADCStreamClient*, std::string) {}
    virtual void stoppedNoActiveChannels(ADCStreamClient*, std::string) {}
    virtual void stoppedMemError(ADCStreamClient*, std::string) {}
    virtual void stoppedMemModify(ADCStreamClient*, std::string) {}
    virtual void stoppedSDFull(ADCStreamClient*, std::string) {}
    virtual void stoppedSDDone(ADCStreamClient*, std::string) {}

    virtual void configConnected(ADCStreamClient*, std::string) {}
    virtual void configError(ADCStreamClient*, std::string, int) {}
    virtual void configErrorTimeout(ADCStreamClient*, std::string) {}
};

class DACCallback {
   public:
    virtual ~DACCallback() {}
    virtual void sendedPack(DACStreamClient*, uint32_t ch1_size, uint32_t ch2_size) {}
    virtual void connected(DACStreamClient*, std::string) {}
    virtual void disconnected(DACStreamClient*, std::string) {}
    virtual void error(DACStreamClient*, std::string, int) {}
    virtual void stopped(DACStreamClient*, std::string) {}
    virtual void stoppedFileEnd(DACStreamClient*, std::string) {}
    virtual void stoppedFileBroken(DACStreamClient*, std::string) {}
    virtual void stoppedEmpty(DACStreamClient*, std::string) {}
    virtual void stoppedMissingFile(DACStreamClient*, std::string) {}
    virtual void stoppedMemError(DACStreamClient*, std::string) {}
    virtual void stoppedMemModify(DACStreamClient*, std::string) {}

    virtual void configConnected(DACStreamClient*, std::string) {}
    virtual void configError(DACStreamClient*, std::string, int) {}
    virtual void configErrorTimeout(DACStreamClient*, std::string) {}
};







class DACStreamClient
{
public:
    DACStreamClient();
    ~DACStreamClient();

    auto connect() -> bool;
    auto connect(std::string host) -> bool;

    auto setRepeatCount(uint64_t count) -> void;
    auto setRepeatInf(bool enable) -> void;
    auto setMemory8Bit(uint8_t channel, std::vector<int8_t> buffer) -> bool;
    auto setMemory16Bit(uint8_t channel, std::vector<int16_t> buffer) -> bool;

    auto startStreamingTDMS(std::string fileName) -> bool;
    auto startStreamingWAV(std::string fileName) -> bool;
    auto startStreamingFromMemory() -> bool;
    auto stopStreaming() -> void;

    auto wait() -> void;
    auto notifyStop() -> void;

    auto sendConfig(std::string key, std::string value) -> bool;
    auto sendConfig(std::string host, std::string key, std::string value) -> bool;
    auto getConfig(std::string key) -> std::string;
    auto getConfig(std::string host, std::string key) -> std::string;

    auto sendFileConfig(std::string config) -> bool;
    auto sendFileConfig(std::string host, std::string config) -> bool;
    auto getFileConfig() -> std::string;
    auto getFileConfig(std::string host) -> std::string;

    auto setVerbose(bool enable) -> void;

    auto setCallbackFunction(DACCallback *callback) -> void;
    auto removeCallbackFunction() -> void;

private:
    auto startStreaming() -> bool;

    struct Impl;
    // Pointer to the internal implementation
    Impl *m_pimpl;
};

class ADCStreamClient {
   public:
    ADCStreamClient();
    ~ADCStreamClient();

    auto connect() -> bool;
    auto connect(std::vector<std::string> hosts) -> bool;

    auto startStreaming() -> bool;
    auto stopStreaming() -> void;
    auto wait() -> void;
    auto notifyStop() -> void;
    auto notifyStop(std::string host) -> void;

    auto sendConfig(std::string key, std::string value) -> bool;
    auto sendConfig(std::string host, std::string key, std::string value) -> bool;
    auto getConfig(std::string key) -> std::string;
    auto getConfig(std::string host, std::string key) -> std::string;

    auto sendFileConfig(std::string config) -> bool;
    auto sendFileConfig(std::string host, std::string config) -> bool;
    auto getFileConfig() -> std::string;
    auto getFileConfig(std::string host) -> std::string;

    auto setVerbose(bool enable) -> void;

    auto setReciveDataFunction(ADCCallback* callback) -> void;
    auto removeReciveDataFunction() -> void;

   private:
    struct Impl;
    // Pointer to the internal implementation
    Impl* m_pimpl;
};