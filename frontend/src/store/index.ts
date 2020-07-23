import { configureStore } from "@reduxjs/toolkit";
import { objectListReducer } from "./objectList";
import { objectSelectorReducer } from "./objectSelector";

const store = configureStore({
    reducer: {
        objectList: objectListReducer,
        objectSelector: objectSelectorReducer,
    },
});

export default store;

export type RootState = ReturnType<typeof store.getState>;
export type Dispatch = typeof store.dispatch;
