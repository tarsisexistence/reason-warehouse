type state =
  | LoadingDogs
  | ErrorFetchingDogs
  | LoadedDogs(array(string));

[@react.component]
let make = (~children) => {
  <div
    className="container"
    style={ReactDOMRe.Style.make(
      ~color="var(--textNormal)",
      ~background="var(--bg)",
      ~transition="color 0.2s ease-out, background 0.2s ease-out",
      ~minHeight="100vh",
      (),
    )}>
    children
  </div>;
};