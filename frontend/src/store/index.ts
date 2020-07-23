import { createStore } from "redux";
import rootReducer from "src/store/reducers";
import { init, RematchRootState, RematchDispatch } from "@rematch/core";
import { models, RootModel } from "./models";
import { objectSelector } from "./objectSelector";

const store = init({ models });

export default store;

export type Store = typeof store;
export type Dispatch = RematchDispatch<RootModel>;
export type RootState = RematchRootState<RootModel>;
