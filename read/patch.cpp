#pragma XOD evaluate_on_pin disable
#pragma XOD evaluate_on_pin enable input_UPD

node {
    void evaluate(Context ctx) {
        // The node responds only if there is an input pulse
        if (!isInputDirty<input_UPD>(ctx))
            return;

        auto sensor = getValue<input_DEV>(ctx);
        int errorCode = sensor->read();
        emitValue<output_Error>(ctx, abs(errorCode));
        if (errorCode!=0) {
            raiseError<output_RH>(ctx);
            raiseError<output_Temp>(ctx);
            raiseError<output_Done>(ctx);
        } else {
            emitValue<output_RH>(ctx, sensor->getHumidity());
            emitValue<output_Temp>(ctx, sensor->getTemperature());
            emitValue<output_Done>(ctx, 1);
        }
    }
}
